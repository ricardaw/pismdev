// Copyright (C) 2011, 2012 PISM Authors
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

#ifndef _POOCEANBOXMODEL_H_
#define _POOCEANBOXMODEL_H_

#include "PGivenClimate.hh"
#include "POModifier.hh"
#include "Timeseries.hh"

//! A class defining the interface of a PISM ocean model modifier.

//! \brief A class implementing an ocean model.
//! Computes the subshelf melt/refreezing rate based on a simple ocean box model by Olbers & Hellmer (2010).
//class POoceanboxmodel : public PISMOceanModel {
//public:
   //POoceanboxmodel(IceGrid &g, const NCConfigVariable &conf);
   
//class POoceanboxmodel : public PGivenClimate<POModifier,PISMOceanModel>
//{
class POoceanboxmodel : public PISMOceanModel {
public:
  POoceanboxmodel(IceGrid &g, const NCConfigVariable &conf);
  //  : PGivenClimate<POModifier,PISMOceanModel>(g, conf, NULL)
  //{
  //  temp_name       = "thetao";
  //  mass_flux_name  = "salinity"; //NOTE: salinity_name instead of mass_flux_name
  //  option_prefix   = "-oceanboxmodel"; // Ronja: changed from -ocean_boxmodel

//    obm_deltaT_set = false;
//    delta_T = NULL;
 // }

  virtual ~POoceanboxmodel() {}

  virtual PetscErrorCode init(PISMVars &vars);
  virtual PetscErrorCode update(PetscReal my_t, PetscReal my_dt) { t = my_t; dt = my_dt; return 0; } // do nothing //FIXME is this correct?

  virtual PetscErrorCode sea_level_elevation(PetscReal &result) { //FIXME is this obsolete?
    result = sea_level;
    return 0;
  }
  virtual PetscErrorCode AntarcticBasins();
  virtual PetscErrorCode extentOfIceShelves();
  virtual PetscErrorCode identifyGroundingLineBox();
  virtual PetscErrorCode identifyIceFrontBox();
  virtual PetscErrorCode oceanTemperature(); 
  virtual PetscErrorCode basalMeltRateForGroundingLineBox(); 
  virtual PetscErrorCode basalMeltRateForIceFrontBox(); 
  virtual PetscErrorCode basalMeltRateForOtherShelves(); 
  
   virtual PetscErrorCode shelf_base_temperature(IceModelVec2S &result);
   virtual PetscErrorCode shelf_base_mass_flux(IceModelVec2S &result);

   virtual void add_vars_to_output(string keyword, map<string,NCSpatialVariable> &result);
   virtual PetscErrorCode define_variables(set<string> vars, const PIO &nc,
                                          PISM_IO_Type nctype);
   virtual PetscErrorCode write_variables(set<string> vars, string filename);

protected:
  IceModelVec2S *ice_thickness, *topg, *lat, *lon;	// not owned by this class
  IceModelVec2S SHELFmask, BOXMODELmask, Soc, Soc_base, Toc, Toc_base, Toc_inCelsius, T_star, Toc_anomaly, overturning, heatflux, basalmeltrate_shelf;
  NCSpatialVariable shelfbmassflux, shelfbtemp;
  bool obm_deltaT_set;
  Timeseries *delta_T;
  
//  bool firstOceanBoxModelStep;
//   static const int basin_RossSea, basin_WeddellSea, basin_EastAntarctica, basin_AmundsenSea, box_near_GL; 
  static const int shelf_unidentified, noshelf, shelf_RossSea, shelf_WeddellSea, shelf_EastAntarctica, shelf_AmundsenSea;
  static const int box_unidentified, box_noshelf, box_GL, box_near_GL, box_IF;
  PetscScalar counterRoss, counterWeddell, counterEastAntarctica, counterAmundsen; // size of each shelf
  PetscScalar counterRoss_init, counterWeddell_init, counterEastAntarctica_init, counterAmundsen_init; // initial size of each shelf
  PetscScalar counterRoss_GLbox, counterWeddell_GLbox, counterEastAntarctica_GLbox, counterAmundsen_GLbox; // size of grounding line box
  PetscScalar counterRoss_CFbox, counterWeddell_CFbox, counterEastAntarctica_CFbox, counterAmundsen_CFbox; // size of ice front box
  PetscScalar k_Ross, k_Weddell, k_EastAntarctica, k_Amundsen; // determines the number of cells accounting for the grounding line and ice front boxes  

  PetscScalar mean_salinity_Ross_GLbox, mean_salinity_Weddell_GLbox, mean_salinity_EastAntarctica_GLbox, mean_salinity_Amundsen_GLbox;
  PetscScalar mean_meltrate_Ross_GLbox, mean_meltrate_Weddell_GLbox, mean_meltrate_EastAntarctica_GLbox, mean_meltrate_Amundsen_GLbox;
  PetscScalar mean_overturning_Ross_GLbox, mean_overturning_Weddell_GLbox, mean_overturning_EastAntarctica_GLbox, mean_overturning_Amundsen_GLbox;
};

#endif /* _POOCEANBOXMODEL_H_ */
