// Copyright (C) 2008 Ed Bueler
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "iceCalvBCModel.hh"


IceCalvBCModel::IceCalvBCModel(IceGrid &g, IceType *i, const char mytest)
  : IceExactSSAModel(g, i, mytest) {
}


IceCalvBCModel::~IceCalvBCModel() {
  vsmoothCFmask.destroy();
  vnCF[0].destroy();
  vnCF[1].destroy();
}


PetscErrorCode IceCalvBCModel::initFromOptions(PetscTruth doHook) {
  PetscErrorCode  ierr;

  // create just like in parent
  ierr = IceExactSSAModel::initFromOptions(doHook); CHKERRQ(ierr);

  // additionally create this stuff
  ierr = vsmoothCFmask.create(grid, "smoothCFmask", true); CHKERRQ(ierr); // stencil = BOX
  ierr = vsmoothCFmask.set_attrs(  // no pism_intent; no standard_name
           "NONE", "smoothed version of (thk>0) mask, for calving front normal direction", 
           "1", NULL); CHKERRQ(ierr);  
  ierr = vnCF[0].create(grid, "nCF_x", true); CHKERRQ(ierr);
  ierr = vnCF[0].set_attrs(  // no pism_intent; no standard_name
           "NONE", "x component of calving front normal direction", 
           "m-1", NULL); CHKERRQ(ierr);  
  ierr = vnCF[1].create(grid, "nCF_y", true); CHKERRQ(ierr);
  ierr = vnCF[1].set_attrs(  // no pism_intent; no standard_name
           "NONE", "y component of calving front normal direction", 
           "m-1", NULL); CHKERRQ(ierr);  
  return 0;
}


PetscErrorCode IceCalvBCModel::compute_nCF() {
  PetscErrorCode ierr;

  PetscScalar     **cfmask, **ncf[2], **H;

  // toss out old values
  ierr = vsmoothCFmask.set(0.0); CHKERRQ(ierr);
  ierr = vnCF[0].set(0.0); CHKERRQ(ierr);  // temp storage in mask smooth

  // smoothCFmask is smoothed version of (H>100) mask
  ierr = vsmoothCFmask.get_array(cfmask); CHKERRQ(ierr);
  ierr = vH.get_array(H); CHKERRQ(ierr);
  for (PetscInt i=grid.xs; i<grid.xs+grid.xm; ++i) {
    for (PetscInt j=grid.ys; j<grid.ys+grid.ym; ++j) {
      if (H[i][j] <= 0.001)       cfmask[i][j] = 0.0;
      else if  (H[i][j] >= 100.0) cfmask[i][j] = 1.0;
      else                        cfmask[i][j] = H[i][j] / 100.0;
    }
  }
  ierr = vsmoothCFmask.end_access(); CHKERRQ(ierr);
  ierr = vH.end_access(); CHKERRQ(ierr);

  // smooth by iterated averaging
  IceModelVec2 vnCFOLD = vnCF[0];
  PetscScalar **cfOLD;
  const PetscInt smoothStages = 3;
  for (PetscInt k=0; k<smoothStages; ++k) {
    // communicate/copy to get valid ghost, into "OLD" copy
    ierr = vsmoothCFmask.beginGhostComm(vnCFOLD); CHKERRQ(ierr);
    ierr = vsmoothCFmask.endGhostComm(vnCFOLD); CHKERRQ(ierr);
    // now smooth
    ierr = vsmoothCFmask.get_array(cfmask); CHKERRQ(ierr);
    ierr = vnCFOLD.get_array(cfOLD); CHKERRQ(ierr);
    for (PetscInt i=grid.xs; i<grid.xs+grid.xm; ++i) {
      for (PetscInt j=grid.ys; j<grid.ys+grid.ym; ++j) {
        cfmask[i][j] = 
           0.075 * cfOLD[i-1][j+1] + 0.15 * cfOLD[i][j+1] + 0.075 * cfOLD[i+1][j+1] 
         + 0.15  * cfOLD[i-1][j]   + 0.1  * cfOLD[i][j]   + 0.15  * cfOLD[i+1][j] 
         + 0.075 * cfOLD[i-1][j-1] + 0.15 * cfOLD[i][j-1] + 0.075 * cfOLD[i+1][j-1]; 
      }
    }
    ierr = vsmoothCFmask.end_access(); CHKERRQ(ierr);
    ierr = vnCFOLD.end_access(); CHKERRQ(ierr);
  }

  // communicate one more time for ghosts for gradient calculation
  ierr = vsmoothCFmask.beginGhostComm(); CHKERRQ(ierr);
  ierr = vsmoothCFmask.endGhostComm(); CHKERRQ(ierr);

  // calving front normal direction is negative of gradient of smoothCFmask:
  ierr = vsmoothCFmask.get_array(cfmask); CHKERRQ(ierr);
  ierr = vnCF[0].get_array(ncf[0]); CHKERRQ(ierr);
  ierr = vnCF[1].get_array(ncf[1]); CHKERRQ(ierr);
  for (PetscInt i=grid.xs; i<grid.xs+grid.xm; ++i) {
    for (PetscInt j=grid.ys; j<grid.ys+grid.ym; ++j) {
      ncf[0][i][j] = - (cfmask[i+1][j] - cfmask[i-1][j]) / (2.0 * grid.dx);
      ncf[1][i][j] = - (cfmask[i][j+1] - cfmask[i][j-1]) / (2.0 * grid.dy);
    }
  } 
  ierr = vsmoothCFmask.end_access(); CHKERRQ(ierr);
  ierr = vnCF[0].end_access(); CHKERRQ(ierr);
  ierr = vnCF[1].end_access(); CHKERRQ(ierr);

  return 0;
}


PetscErrorCode IceCalvBCModel::writeCFfields(const char* default_filename) {
  PetscErrorCode ierr;
  
  char filename[PETSC_MAX_PATH_LEN];
  PetscTruth o_set;
  ierr = PetscOptionsGetString(PETSC_NULL, "-o", filename, PETSC_MAX_PATH_LEN, &o_set); CHKERRQ(ierr);

  // Use the default if the output file name was not given:
  if (!o_set)
    strncpy(filename, default_filename, PETSC_MAX_PATH_LEN);

  ierr = vsmoothCFmask.write(filename, NC_DOUBLE); CHKERRQ(ierr);
  ierr = vnCF[0].write(filename, NC_DOUBLE); CHKERRQ(ierr);
  ierr = vnCF[1].write(filename, NC_DOUBLE); CHKERRQ(ierr);
  return 0;
}


PetscErrorCode IceCalvBCModel::assembleSSAMatrix(const bool includeBasalShear,
                                 IceModelVec2 vNuH[2], Mat A) {
  const PetscInt  Mx=grid.Mx, My=grid.My, M=2*My;
  const PetscScalar   dx=grid.dx, dy=grid.dy;
  const PetscScalar   one = 1.0;
  PetscErrorCode  ierr;
  PetscScalar     **mask, **nuH[2], **u, **v, **tauc;

  ierr = MatZeroEntries(A); CHKERRQ(ierr);

  /* matrix assembly loop */
  ierr = vMask.get_array(mask); CHKERRQ(ierr);
  ierr = vtauc.get_array(tauc); CHKERRQ(ierr);
  ierr = vubarSSA.get_array(u); CHKERRQ(ierr);
  ierr = vvbarSSA.get_array(v); CHKERRQ(ierr);
  ierr = vNuH[0].get_array(nuH[0]); CHKERRQ(ierr);
  ierr = vNuH[1].get_array(nuH[1]); CHKERRQ(ierr);

  for (PetscInt i=grid.xs; i<grid.xs+grid.xm; ++i) {
    for (PetscInt j=grid.ys; j<grid.ys+grid.ym; ++j) {
      const PetscInt J = 2*j;
      const PetscInt rowU = i*M + J;
      const PetscInt rowV = i*M + J+1;
      if (intMask(mask[i][j]) == MASK_SHEET) {
        // set diagonal entry to one; RHS entry will be known (e.g. SIA) velocity;
        //   this is where boundary value to SSA is set
        ierr = MatSetValues(A, 1, &rowU, 1, &rowU, &one, INSERT_VALUES); CHKERRQ(ierr);
        ierr = MatSetValues(A, 1, &rowV, 1, &rowV, &one, INSERT_VALUES); CHKERRQ(ierr);
      } else {
        const PetscInt im = (i + Mx - 1) % Mx, ip = (i + 1) % Mx;
        const PetscInt Jm = 2 * ((j + My - 1) % My), Jp = 2 * ((j + 1) % My);
        const PetscScalar dx2 = dx*dx, d4 = dx*dy*4, dy2 = dy*dy;
        /* Provide shorthand for the following staggered coefficients
        *      c11
        *  c00     c01
        *      c10
        * Note that the positive i (x) direction is right and the positive j (y)
        * direction is up. */

        // thickness H is incorporated here because nuH[][][] is actually 
        //   viscosity times thickness
        const PetscScalar c00 = nuH[0][i-1][j];
        const PetscScalar c01 = nuH[0][i][j];
        const PetscScalar c10 = nuH[1][i][j-1];
        const PetscScalar c11 = nuH[1][i][j];

        const PetscInt stencilSize = 13;
        /* The locations of the stencil points for the U equation */
        const PetscInt colU[] = {
          /*       */ i*M+Jp,
          im*M+Jp+1,  i*M+Jp+1,   ip*M+Jp+1,
          im*M+J,     i*M+J,      ip*M+J,
          im*M+J+1,               ip*M+J+1,
          /*       */ i*M+Jm,
          im*M+Jm+1,  i*M+Jm+1,   ip*M+Jm+1};
        /* The values at those points */
        PetscScalar valU[] = {
          /*               */ -c11/dy2,
          (2*c00+c11)/d4,     2*(c00-c01)/d4,                 -(2*c01+c11)/d4,
          -4*c00/dx2,         4*(c01+c00)/dx2+(c11+c10)/dy2,  -4*c01/dx2,
          (c11-c10)/d4,                                       (c10-c11)/d4,
          /*               */ -c10/dy2,
          -(2*c00+c10)/d4,    2*(c01-c00)/d4,                 (2*c01+c10)/d4 };

        /* The locations of the stencil points for the V equation */
        const PetscInt colV[] = {
          im*M+Jp,        i*M+Jp,     ip*M+Jp,
          /*           */ i*M+Jp+1,
          im*M+J,                     ip*M+J,
          im*M+J+1,       i*M+J+1,    ip*M+J+1,
          im*M+Jm,        i*M+Jm,     ip*M+Jm,
          /*           */ i*M+Jm+1 };
        /* The values at those points */
        PetscScalar valV[] = {
          (2*c11+c00)/d4,     (c00-c01)/d4,                   -(2*c11+c01)/d4,
          /*               */ -4*c11/dy2,
          2*(c11-c10)/d4,                                     2*(c10-c11)/d4,
          -c00/dx2,           4*(c11+c10)/dy2+(c01+c00)/dx2,  -c01/dx2,
          -(2*c10+c00)/d4,    (c01-c00)/d4,                   (2*c10+c01)/d4,
          /*               */ -4*c10/dy2 };

        /* Dragging ice experiences friction at the bed determined by the
         *    basalDrag[x|y]() methods.  These may be a plastic, pseudo-plastic,
         *    or linear friction law according to basal->drag(), which gets called
         *    by basalDragx(),basalDragy().  */
        if ((includeBasalShear) && (intMask(mask[i][j]) == MASK_DRAGGING)) {
          // Dragging is done implicitly (i.e. on left side of SSA eqns for u,v).
          valU[5] += basalDragx(tauc, u, v, i, j);
          valV[7] += basalDragy(tauc, u, v, i, j);
        }

        // make shelf drag a little bit if desired
        if ((shelvesDragToo == PETSC_TRUE) && (intMask(mask[i][j]) == MASK_FLOATING)) {
          //ierr = verbPrintf(1,grid.com,"... SHELF IS DRAGGING ..."); CHKERRQ(ierr);
          valU[5] += betaShelvesDragToo;
          valV[7] += betaShelvesDragToo;
        }

        ierr = MatSetValues(A, 1, &rowU, stencilSize, colU, valU, INSERT_VALUES); CHKERRQ(ierr);
        ierr = MatSetValues(A, 1, &rowV, stencilSize, colV, valV, INSERT_VALUES); CHKERRQ(ierr);
      }
    }
  }
  ierr = vMask.end_access(); CHKERRQ(ierr);

  ierr = vubarSSA.end_access(); CHKERRQ(ierr);
  ierr = vvbarSSA.end_access(); CHKERRQ(ierr);
  ierr = vtauc.end_access(); CHKERRQ(ierr);

  ierr = vNuH[0].end_access(); CHKERRQ(ierr);
  ierr = vNuH[1].end_access(); CHKERRQ(ierr);

  ierr = MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  ierr = MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY); CHKERRQ(ierr);
  return 0;
}



PetscErrorCode IceCalvBCModel::assembleSSARhs(bool surfGradInward, Vec rhs) {
  PetscErrorCode  ierr;

  const PetscInt  Mx=grid.Mx, My=grid.My, M=2*My;
  const PetscScalar   dx=grid.dx, dy=grid.dy;

  // first, find and store normal direction to calving front;
  // used in forming both rhs and A
  ierr = compute_nCF(); CHKERRQ(ierr);

  PetscScalar     **mask, **h, **H, **uvbar[2], **taudx, **taudy;

  ierr = VecSet(rhs, 0.0); CHKERRQ(ierr);

  // get driving stress components
  ierr = computeDrivingStress(vWork2d[0],vWork2d[1]); CHKERRQ(ierr); // in iMutil.cc
  ierr = vWork2d[0].get_array(taudx); CHKERRQ(ierr);
  ierr = vWork2d[1].get_array(taudy); CHKERRQ(ierr);

  /* rhs (= right-hand side) assembly loop */
  ierr = vMask.get_array(mask); CHKERRQ(ierr);
  ierr = vh.get_array(h); CHKERRQ(ierr);
  ierr = vH.get_array(H); CHKERRQ(ierr);
  ierr = vuvbar[0].get_array(uvbar[0]); CHKERRQ(ierr);
  ierr = vuvbar[1].get_array(uvbar[1]); CHKERRQ(ierr);
  for (PetscInt i=grid.xs; i<grid.xs+grid.xm; ++i) {
    for (PetscInt j=grid.ys; j<grid.ys+grid.ym; ++j) {
      const PetscInt J = 2*j;
      const PetscInt rowU = i*M + J;
      const PetscInt rowV = i*M + J+1;
      if (intMask(mask[i][j]) == MASK_SHEET) {
        ierr = VecSetValue(rhs, rowU, 0.5*(uvbar[0][i-1][j] + uvbar[0][i][j]),
                           INSERT_VALUES); CHKERRQ(ierr);
        ierr = VecSetValue(rhs, rowV, 0.5*(uvbar[1][i][j-1] + uvbar[1][i][j]),
                           INSERT_VALUES); CHKERRQ(ierr);
      } else {
        bool edge = ((i == 0) || (i == Mx-1) || (j == 0) || (j == My-1));
        if (surfGradInward && edge) {
          PetscScalar h_x, h_y;
          if (i == 0) {
            h_x = (h[i+1][j] - h[i][j]) / (dx);
            h_y = (h[i][j+1] - h[i][j-1]) / (2*dy);
          } else if (i == Mx-1) {
            h_x = (h[i][j] - h[i-1][j]) / (dx);
            h_y = (h[i][j+1] - h[i][j-1]) / (2*dy);
          } else if (j == 0) {
            h_x = (h[i+1][j] - h[i-1][j]) / (2*dx);
            h_y = (h[i][j+1] - h[i][j]) / (dy);
          } else if (j == My-1) {        
            h_x = (h[i+1][j] - h[i-1][j]) / (2*dx);
            h_y = (h[i][j] - h[i][j-1]) / (dy);
          } else {
            SETERRQ(1,"should not reach here: surfGradInward=TRUE & edge=TRUE but not at edge");
          }          
          const PetscScalar pressure = ice->rho * grav * H[i][j];
          ierr = VecSetValue(rhs, rowU, - pressure * h_x, INSERT_VALUES); CHKERRQ(ierr);
          ierr = VecSetValue(rhs, rowV, - pressure * h_y, INSERT_VALUES); CHKERRQ(ierr);
        } else { // usual case: use already computed driving stress
          ierr = VecSetValue(rhs, rowU, taudx[i][j], INSERT_VALUES); CHKERRQ(ierr);
          ierr = VecSetValue(rhs, rowV, taudy[i][j], INSERT_VALUES); CHKERRQ(ierr);          
        }
      }
    }
  }
  ierr = vMask.end_access(); CHKERRQ(ierr);
  ierr = vh.end_access(); CHKERRQ(ierr);
  ierr = vH.end_access(); CHKERRQ(ierr);
  ierr = vuvbar[0].end_access(); CHKERRQ(ierr);
  ierr = vuvbar[1].end_access(); CHKERRQ(ierr);

  ierr = vWork2d[0].end_access(); CHKERRQ(ierr);
  ierr = vWork2d[1].end_access(); CHKERRQ(ierr);

  ierr = VecAssemblyBegin(rhs); CHKERRQ(ierr);
  ierr = VecAssemblyEnd(rhs); CHKERRQ(ierr);
  return 0;
}
