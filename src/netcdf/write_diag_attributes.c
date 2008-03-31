// This file was automatically generated by `ncgen.rb' from
// `pism_state.cdl' and 'pism_diag.fragment'.  If you edit it,
// your changes will be overwritten
// on the next invocation of `ncgen.rb'.

   int  stat;			/* return status */
   int  ncid;			/* netCDF id */

   /* dimension ids */
   int x_dim;
   int y_dim;
   int z_dim;
   int zb_dim;
   int t_dim;

   /* dimension lengths */
   size_t x_len = grid.Mx;
   size_t y_len = grid.My;
   size_t z_len = grid.Mz;
   size_t zb_len = grid.Mbz;
   size_t t_len = NC_UNLIMITED;

   /* variable ids */
   int polar_stereographic_id;
   int x_id;
   int y_id;
   int z_id;
   int zb_id;
   int t_id;
   int lon_id;
   int lat_id;
   int mask_id;
   int thk_id;
   int bwat_id;
   int topg_id;
   int dbdt_id;
   int temp_id;
   int litho_temp_id;
   int age_id;
   int artm_id;
   int bheatflx_id;
   int acab_id;
   int tillphi_id;
   int usurf_id;
   int dHdt_id;
   int cbar_id;
   int cbase_id;
   int csurf_id;
   int wsurf_id;
   int cflx_id;
   int taub_id;
   int tauc_id;
   int uvel_id;
   int vvel_id;
   int wvel_id;

   /* rank (number of dimensions) for each variable */
#  define RANK_polar_stereographic 0
#  define RANK_x 1
#  define RANK_y 1
#  define RANK_z 1
#  define RANK_zb 1
#  define RANK_t 1
#  define RANK_lon 3
#  define RANK_lat 3
#  define RANK_mask 3
#  define RANK_thk 3
#  define RANK_bwat 3
#  define RANK_topg 3
#  define RANK_dbdt 3
#  define RANK_temp 4
#  define RANK_litho_temp 4
#  define RANK_age 4
#  define RANK_artm 3
#  define RANK_bheatflx 3
#  define RANK_acab 3
#  define RANK_tillphi 3
#  define RANK_usurf 3
#  define RANK_dHdt 3
#  define RANK_cbar 3
#  define RANK_cbase 3
#  define RANK_csurf 3
#  define RANK_wsurf 3
#  define RANK_cflx 3
#  define RANK_taub 3
#  define RANK_tauc 3
#  define RANK_uvel 4
#  define RANK_vvel 4
#  define RANK_wvel 4

   /* variable shapes */
   int x_dims[RANK_x];
   int y_dims[RANK_y];
   int z_dims[RANK_z];
   int zb_dims[RANK_zb];
   int t_dims[RANK_t];
   int lon_dims[RANK_lon];
   int lat_dims[RANK_lat];
   int mask_dims[RANK_mask];
   int thk_dims[RANK_thk];
   int bwat_dims[RANK_bwat];
   int topg_dims[RANK_topg];
   int dbdt_dims[RANK_dbdt];
   int temp_dims[RANK_temp];
   int litho_temp_dims[RANK_litho_temp];
   int age_dims[RANK_age];
   int artm_dims[RANK_artm];
   int bheatflx_dims[RANK_bheatflx];
   int acab_dims[RANK_acab];
   int tillphi_dims[RANK_tillphi];
   int usurf_dims[RANK_usurf];
   int dHdt_dims[RANK_dHdt];
   int cbar_dims[RANK_cbar];
   int cbase_dims[RANK_cbase];
   int csurf_dims[RANK_csurf];
   int wsurf_dims[RANK_wsurf];
   int cflx_dims[RANK_cflx];
   int taub_dims[RANK_taub];
   int tauc_dims[RANK_tauc];
   int uvel_dims[RANK_uvel];
   int vvel_dims[RANK_vvel];
   int wvel_dims[RANK_wvel];

   double polar_stereographic_straight_vertical_longitude_from_pole[1];
   double polar_stereographic_latitude_of_projection_origin[1];
   double polar_stereographic_standard_parallel[1];

   /* enter define mode */
if (grid.rank == 0) {
   stat = nc_create(diag_fname, NC_CLOBBER|NC_64BIT_OFFSET, &ncid);
   check_err(stat,__LINE__,__FILE__);

   /* define dimensions */
   stat = nc_def_dim(ncid, "x", x_len, &x_dim);
   check_err(stat,__LINE__,__FILE__);
   stat = nc_def_dim(ncid, "y", y_len, &y_dim);
   check_err(stat,__LINE__,__FILE__);
   stat = nc_def_dim(ncid, "z", z_len, &z_dim);
   check_err(stat,__LINE__,__FILE__);
   stat = nc_def_dim(ncid, "zb", zb_len, &zb_dim);
   check_err(stat,__LINE__,__FILE__);
   stat = nc_def_dim(ncid, "t", t_len, &t_dim);
   check_err(stat,__LINE__,__FILE__);

   /* define variables */

   stat = nc_def_var(ncid, "polar_stereographic", NC_INT, RANK_polar_stereographic, 0, &polar_stereographic_id);
   check_err(stat,__LINE__,__FILE__);

   x_dims[0] = x_dim;
   stat = nc_def_var(ncid, "x", NC_DOUBLE, RANK_x, x_dims, &x_id);
   check_err(stat,__LINE__,__FILE__);

   y_dims[0] = y_dim;
   stat = nc_def_var(ncid, "y", NC_DOUBLE, RANK_y, y_dims, &y_id);
   check_err(stat,__LINE__,__FILE__);

   z_dims[0] = z_dim;
   stat = nc_def_var(ncid, "z", NC_DOUBLE, RANK_z, z_dims, &z_id);
   check_err(stat,__LINE__,__FILE__);

   zb_dims[0] = zb_dim;
   stat = nc_def_var(ncid, "zb", NC_DOUBLE, RANK_zb, zb_dims, &zb_id);
   check_err(stat,__LINE__,__FILE__);

   t_dims[0] = t_dim;
   stat = nc_def_var(ncid, "t", NC_DOUBLE, RANK_t, t_dims, &t_id);
   check_err(stat,__LINE__,__FILE__);

   lon_dims[0] = t_dim;
   lon_dims[1] = x_dim;
   lon_dims[2] = y_dim;
   stat = nc_def_var(ncid, "lon", NC_FLOAT, RANK_lon, lon_dims, &lon_id);
   check_err(stat,__LINE__,__FILE__);

   lat_dims[0] = t_dim;
   lat_dims[1] = x_dim;
   lat_dims[2] = y_dim;
   stat = nc_def_var(ncid, "lat", NC_FLOAT, RANK_lat, lat_dims, &lat_id);
   check_err(stat,__LINE__,__FILE__);

   mask_dims[0] = t_dim;
   mask_dims[1] = x_dim;
   mask_dims[2] = y_dim;
   stat = nc_def_var(ncid, "mask", NC_BYTE, RANK_mask, mask_dims, &mask_id);
   check_err(stat,__LINE__,__FILE__);

   thk_dims[0] = t_dim;
   thk_dims[1] = x_dim;
   thk_dims[2] = y_dim;
   stat = nc_def_var(ncid, "thk", NC_FLOAT, RANK_thk, thk_dims, &thk_id);
   check_err(stat,__LINE__,__FILE__);

   bwat_dims[0] = t_dim;
   bwat_dims[1] = x_dim;
   bwat_dims[2] = y_dim;
   stat = nc_def_var(ncid, "bwat", NC_FLOAT, RANK_bwat, bwat_dims, &bwat_id);
   check_err(stat,__LINE__,__FILE__);

   topg_dims[0] = t_dim;
   topg_dims[1] = x_dim;
   topg_dims[2] = y_dim;
   stat = nc_def_var(ncid, "topg", NC_FLOAT, RANK_topg, topg_dims, &topg_id);
   check_err(stat,__LINE__,__FILE__);

   dbdt_dims[0] = t_dim;
   dbdt_dims[1] = x_dim;
   dbdt_dims[2] = y_dim;
   stat = nc_def_var(ncid, "dbdt", NC_FLOAT, RANK_dbdt, dbdt_dims, &dbdt_id);
   check_err(stat,__LINE__,__FILE__);

   temp_dims[0] = t_dim;
   temp_dims[1] = x_dim;
   temp_dims[2] = y_dim;
   temp_dims[3] = z_dim;
   stat = nc_def_var(ncid, "temp", NC_FLOAT, RANK_temp, temp_dims, &temp_id);
   check_err(stat,__LINE__,__FILE__);

   litho_temp_dims[0] = t_dim;
   litho_temp_dims[1] = x_dim;
   litho_temp_dims[2] = y_dim;
   litho_temp_dims[3] = zb_dim;
   stat = nc_def_var(ncid, "litho_temp", NC_FLOAT, RANK_litho_temp, litho_temp_dims, &litho_temp_id);
   check_err(stat,__LINE__,__FILE__);

   age_dims[0] = t_dim;
   age_dims[1] = x_dim;
   age_dims[2] = y_dim;
   age_dims[3] = z_dim;
   stat = nc_def_var(ncid, "age", NC_FLOAT, RANK_age, age_dims, &age_id);
   check_err(stat,__LINE__,__FILE__);

   artm_dims[0] = t_dim;
   artm_dims[1] = x_dim;
   artm_dims[2] = y_dim;
   stat = nc_def_var(ncid, "artm", NC_FLOAT, RANK_artm, artm_dims, &artm_id);
   check_err(stat,__LINE__,__FILE__);

   bheatflx_dims[0] = t_dim;
   bheatflx_dims[1] = x_dim;
   bheatflx_dims[2] = y_dim;
   stat = nc_def_var(ncid, "bheatflx", NC_FLOAT, RANK_bheatflx, bheatflx_dims, &bheatflx_id);
   check_err(stat,__LINE__,__FILE__);

   acab_dims[0] = t_dim;
   acab_dims[1] = x_dim;
   acab_dims[2] = y_dim;
   stat = nc_def_var(ncid, "acab", NC_FLOAT, RANK_acab, acab_dims, &acab_id);
   check_err(stat,__LINE__,__FILE__);

   tillphi_dims[0] = t_dim;
   tillphi_dims[1] = x_dim;
   tillphi_dims[2] = y_dim;
   stat = nc_def_var(ncid, "tillphi", NC_FLOAT, RANK_tillphi, tillphi_dims, &tillphi_id);
   check_err(stat,__LINE__,__FILE__);

   usurf_dims[0] = t_dim;
   usurf_dims[1] = x_dim;
   usurf_dims[2] = y_dim;
   stat = nc_def_var(ncid, "usurf", NC_FLOAT, RANK_usurf, usurf_dims, &usurf_id);
   check_err(stat,__LINE__,__FILE__);

   dHdt_dims[0] = t_dim;
   dHdt_dims[1] = x_dim;
   dHdt_dims[2] = y_dim;
   stat = nc_def_var(ncid, "dHdt", NC_FLOAT, RANK_dHdt, dHdt_dims, &dHdt_id);
   check_err(stat,__LINE__,__FILE__);

   cbar_dims[0] = t_dim;
   cbar_dims[1] = x_dim;
   cbar_dims[2] = y_dim;
   stat = nc_def_var(ncid, "cbar", NC_FLOAT, RANK_cbar, cbar_dims, &cbar_id);
   check_err(stat,__LINE__,__FILE__);

   cbase_dims[0] = t_dim;
   cbase_dims[1] = x_dim;
   cbase_dims[2] = y_dim;
   stat = nc_def_var(ncid, "cbase", NC_FLOAT, RANK_cbase, cbase_dims, &cbase_id);
   check_err(stat,__LINE__,__FILE__);

   csurf_dims[0] = t_dim;
   csurf_dims[1] = x_dim;
   csurf_dims[2] = y_dim;
   stat = nc_def_var(ncid, "csurf", NC_FLOAT, RANK_csurf, csurf_dims, &csurf_id);
   check_err(stat,__LINE__,__FILE__);

   wsurf_dims[0] = t_dim;
   wsurf_dims[1] = x_dim;
   wsurf_dims[2] = y_dim;
   stat = nc_def_var(ncid, "wsurf", NC_FLOAT, RANK_wsurf, wsurf_dims, &wsurf_id);
   check_err(stat,__LINE__,__FILE__);

   cflx_dims[0] = t_dim;
   cflx_dims[1] = x_dim;
   cflx_dims[2] = y_dim;
   stat = nc_def_var(ncid, "cflx", NC_FLOAT, RANK_cflx, cflx_dims, &cflx_id);
   check_err(stat,__LINE__,__FILE__);

   taub_dims[0] = t_dim;
   taub_dims[1] = x_dim;
   taub_dims[2] = y_dim;
   stat = nc_def_var(ncid, "taub", NC_FLOAT, RANK_taub, taub_dims, &taub_id);
   check_err(stat,__LINE__,__FILE__);

   tauc_dims[0] = t_dim;
   tauc_dims[1] = x_dim;
   tauc_dims[2] = y_dim;
   stat = nc_def_var(ncid, "tauc", NC_FLOAT, RANK_tauc, tauc_dims, &tauc_id);
   check_err(stat,__LINE__,__FILE__);

   uvel_dims[0] = t_dim;
   uvel_dims[1] = x_dim;
   uvel_dims[2] = y_dim;
   uvel_dims[3] = z_dim;
   stat = nc_def_var(ncid, "uvel", NC_FLOAT, RANK_uvel, uvel_dims, &uvel_id);
   check_err(stat,__LINE__,__FILE__);

   vvel_dims[0] = t_dim;
   vvel_dims[1] = x_dim;
   vvel_dims[2] = y_dim;
   vvel_dims[3] = z_dim;
   stat = nc_def_var(ncid, "vvel", NC_FLOAT, RANK_vvel, vvel_dims, &vvel_id);
   check_err(stat,__LINE__,__FILE__);

   wvel_dims[0] = t_dim;
   wvel_dims[1] = x_dim;
   wvel_dims[2] = y_dim;
   wvel_dims[3] = z_dim;
   stat = nc_def_var(ncid, "wvel", NC_FLOAT, RANK_wvel, wvel_dims, &wvel_id);
   check_err(stat,__LINE__,__FILE__);

   /* assign attributes */
   stat = nc_put_att_text(ncid, polar_stereographic_id, "grid_mapping_name", 19, "polar_stereographic");
   check_err(stat,__LINE__,__FILE__);
   polar_stereographic_straight_vertical_longitude_from_pole[0] = 0;
   stat = nc_put_att_double(ncid, polar_stereographic_id, "straight_vertical_longitude_from_pole", NC_DOUBLE, 1, polar_stereographic_straight_vertical_longitude_from_pole);
   check_err(stat,__LINE__,__FILE__);
   polar_stereographic_latitude_of_projection_origin[0] = 90;
   stat = nc_put_att_double(ncid, polar_stereographic_id, "latitude_of_projection_origin", NC_DOUBLE, 1, polar_stereographic_latitude_of_projection_origin);
   check_err(stat,__LINE__,__FILE__);
   polar_stereographic_standard_parallel[0] = -71;
   stat = nc_put_att_double(ncid, polar_stereographic_id, "standard_parallel", NC_DOUBLE, 1, polar_stereographic_standard_parallel);
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, polar_stereographic_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, x_id, "axis", 1, "X");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, x_id, "long_name", 32, "x-coordinate in Cartesian system");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, x_id, "standard_name", 23, "projection_x_coordinate");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, x_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, x_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, y_id, "axis", 1, "Y");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, y_id, "long_name", 32, "y-coordinate in Cartesian system");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, y_id, "standard_name", 23, "projection_y_coordinate");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, y_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, y_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "axis", 1, "Z");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "long_name", 32, "z-coordinate in Cartesian system");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "standard_name", 23, "projection_z_coordinate");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "positive", 2, "up");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, z_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, zb_id, "long_name", 23, "z-coordinate in bedrock");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, zb_id, "standard_name", 34, "projection_z_coordinate_in_bedrock");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, zb_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, zb_id, "positive", 2, "up");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, zb_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, t_id, "long_name", 4, "time");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, t_id, "units", 33, "seconds since 2007-01-01 00:00:00");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, t_id, "calendar", 4, "none");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, t_id, "axis", 1, "T");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lon_id, "long_name", 9, "longitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lon_id, "standard_name", 9, "longitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lon_id, "units", 12, "degrees_east");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lon_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lat_id, "long_name", 8, "latitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lat_id, "standard_name", 8, "latitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lat_id, "units", 13, "degrees_north");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, lat_id, "pism_intent", 7, "mapping");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, mask_id, "long_name", 39, "grounded_dragging_floating integer mask");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, mask_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, thk_id, "long_name", 18, "land ice thickness");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, thk_id, "standard_name", 18, "land_ice_thickness");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, thk_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, thk_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bwat_id, "long_name", 44, "effective thickness of subglacial melt water");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bwat_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bwat_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, topg_id, "long_name", 25, "bedrock surface elevation");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, topg_id, "standard_name", 16, "bedrock_altitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, topg_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, topg_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dbdt_id, "long_name", 19, "bedrock uplift rate");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dbdt_id, "standard_name", 28, "tendency_of_bedrock_altitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dbdt_id, "units", 5, "m s-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dbdt_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, temp_id, "long_name", 15, "ice temperature");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, temp_id, "standard_name", 20, "land_ice_temperature");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, temp_id, "units", 1, "K");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, temp_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, litho_temp_id, "long_name", 19, "bedrock temperature");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, litho_temp_id, "standard_name", 19, "bedrock_temperature");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, litho_temp_id, "units", 1, "K");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, litho_temp_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, age_id, "long_name", 10, "age of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, age_id, "standard_name", 12, "land_ice_age");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, age_id, "units", 1, "s");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, age_id, "pism_intent", 11, "model_state");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, artm_id, "long_name", 42, "annual mean air temperature at ice surface");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, artm_id, "standard_name", 19, "surface_temperature");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, artm_id, "units", 1, "K");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, artm_id, "pism_intent", 14, "climate_steady");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bheatflx_id, "long_name", 41, "upward geothermal flux at bedrock surface");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bheatflx_id, "units", 5, "W m-2");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, bheatflx_id, "pism_intent", 14, "climate_steady");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, acab_id, "long_name", 59, "mean annual net ice equivalent accumulation (ablation) rate");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, acab_id, "standard_name", 38, "land_ice_surface_specific_mass_balance");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, acab_id, "units", 5, "m s-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, acab_id, "pism_intent", 14, "climate_steady");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tillphi_id, "long_name", 48, "friction angle for till under grounded ice sheet");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tillphi_id, "units", 7, "degrees");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tillphi_id, "pism_intent", 14, "climate_steady");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, usurf_id, "long_name", 27, "ice upper surface elevation");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, usurf_id, "standard_name", 16, "surface_altitude");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, usurf_id, "units", 1, "m");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, usurf_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dHdt_id, "long_name", 31, "rate of change of ice thickness");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dHdt_id, "units", 8, "m year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, dHdt_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbar_id, "long_name", 61, "magnitude of vertically-integrated horizontal velocity of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbar_id, "units", 8, "m year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbar_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbase_id, "long_name", 54, "magnitude of horizontal velocity of ice at base of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbase_id, "units", 8, "m year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cbase_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, csurf_id, "long_name", 54, "magnitude of horizontal velocity of ice at ice surface");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, csurf_id, "units", 8, "m year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, csurf_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wsurf_id, "long_name", 39, "vertical velocity of ice at ice surface");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wsurf_id, "units", 8, "m year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wsurf_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cflx_id, "long_name", 57, "magnitude of vertically-integrated horizontal flux of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cflx_id, "units", 9, "m2 year-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, cflx_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, taub_id, "long_name", 48, "magnitude of driving shear stress at base of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, taub_id, "units", 2, "Pa");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, taub_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tauc_id, "long_name", 61, "yield stress for basal till (plastic or pseudo-plastic model)");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tauc_id, "units", 2, "Pa");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, tauc_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, uvel_id, "long_name", 63, "horizontal velocity of ice in projection_x_coordinate direction");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, uvel_id, "units", 5, "m s-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, uvel_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, vvel_id, "long_name", 63, "horizontal velocity of ice in projection_y_coordinate direction");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, vvel_id, "units", 5, "m s-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, vvel_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wvel_id, "long_name", 24, "vertical velocity of ice");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wvel_id, "units", 5, "m s-1");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, wvel_id, "pism_intent", 10, "diagnostic");
   check_err(stat,__LINE__,__FILE__);
   stat = nc_put_att_text(ncid, NC_GLOBAL, "Conventions", 6, "CF-1.0");
   check_err(stat,__LINE__,__FILE__);

} // end if (grid.rank == 0)
