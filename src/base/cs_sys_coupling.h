#ifndef __CS_SYS_COUPLING_H__
#define __CS_SYS_COUPLING_H__

/*============================================================================
 * SYSTEM Scale code coupling (0D/1D equations)
 *============================================================================*/

/*
  This file is part of Code_Saturne, a general-purpose CFD tool.

  Copyright (C) 1998-2023 EDF S.A.

  This program is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 2 of the License, or (at your option) any later
  version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
  Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/*----------------------------------------------------------------------------
 * Local headers
 *----------------------------------------------------------------------------*/

#include "cs_base.h"
#include "cs_zone.h"

/*----------------------------------------------------------------------------*/

BEGIN_C_DECLS

typedef enum
{
  CS_SYS_CPL_BC_INLET,
  CS_SYS_CPL_BC_OUTLET,
  CS_SYS_CPL_BC_WALL,
  CS_SYS_CPL_BC_VOLUME,

  CS_N_SYS_CPL_BC_TYPES,

  CS_SYS_CPL_BC_UKNOWN
} cs_syscpl_bc_type_t;

typedef struct {

  // Intersection (surface/volume)
  int              *n_elts;       // Number of intersected sys elts for each CFD elt
  cs_double_int_t **elt_ids_val;  // Surface/Volume intersected (absolute!) + id

  cs_real_t *cfd_weight; // Total weight for cfd elements
  cs_real_t *sys_weight; // Total weight for sys elements

} cs_cfd2sys_intersection_t;

typedef struct {

  // Coupling type
  cs_syscpl_bc_type_t type;

  // Coupling zones. If in/out are different both are used, otherwise only
  // first.
  int input_zone_id;

  char *selection_criteria_output;

  // Inverse flow rate (normal) if necessary
  int bnd_dir;

  // Surface coefficient used for symmetrical cases.
  cs_real_t surf_coeff;

  // Fields to send
  int  n_send_fields;
  int *send_field_ids;

  // Fields to send
  int  n_recv_fields;
  int *recv_field_ids;

  // Number of elements in system code
  int n_sys_elts;                 // 1 For 0D, > 1 for a 1D element
  cs_cfd2sys_intersection_t *im;  // NULL for 0D, !=NULL for a 1D element

  // System element identification
  char  *element_name;
  int    sys_elt_idx[2];

} cs_cfd_sys_cplbc_t;

typedef struct {

  // ---------------------------
  // MPI Parameters
#if defined(HAVE_MPI)
  MPI_Comm comm;
#endif

  int cfd_root;
  int sys_root;
  int sys_n_ranks;
  // ---------------------------

  // ---------------------------
  // Coupling zones
  int                  n_cpl_bcs;
  cs_cfd_sys_cplbc_t **cplbc;
  // ---------------------------

  // ---------------------------
  // send/recv arrays
  int        n_send_vals;
  cs_real_t *send_vals;
  int        n_recv_vals;
  cs_real_t *recv_vals;
  // ---------------------------

  // ---------------------------
  // Number of coupled phases
  int n_cpl_phases;
  // ---------------------------

  // ---------------------------
  // system code instance
  char *sys_name;
  // ---------------------------

} cs_sys_cpl_t;

/*----------------------------------------------------------------------------*/
/* Public functions */
/*----------------------------------------------------------------------------*/

cs_sys_cpl_t *
cs_sys_coupling_by_id(const int cpl_id);

cs_sys_cpl_t *
cs_sys_coupling_by_name_try(const char *sys_name);

cs_sys_cpl_t *
cs_sys_coupling_by_name(const char *sys_name);

void
cs_sys_cplbc_add_field_to_send(cs_cfd_sys_cplbc_t *cplbc,
                               const int           field_id);

void
cs_sys_cplbc_add_field_to_recv(cs_cfd_sys_cplbc_t *cplbc,
                               const int           field_id);

void
cs_sys_cplbc_define_surf_coeff(cs_cfd_sys_cplbc_t *cplbc,
                               const cs_real_t     coeff);

void
cs_sys_cplbc_inverse_bnd_dir(cs_cfd_sys_cplbc_t *cplbc);

void
cs_sys_cplbc_add_exchanged_field(cs_cfd_sys_cplbc_t *cplbc,
                                 const int           dir,
                                 const int           field_id);

void
cs_sys_coupling_add_cplbc(cs_sys_cpl_t        *sys_coupling,
                          cs_syscpl_bc_type_t  type,
                          const cs_zone_t     *z_input,
                          const char          *sel_criteria_output,
                          const char          *element_name,
                          const int            c0,
                          const int            c1,
                          const int            n_sys_elts);

int
cs_sys_coupling_add(const char *sys_name,
                    const int   n_cpl_phases);

void
cs_sys_coupling_send_data(cs_sys_cpl_t *cpl);

void
cs_sys_coupling_recv_data(cs_sys_cpl_t *cpl);

void
cs_sys_coupling_all_init(void);

void
cs_sys_coupling_all_finalize(void);
/*----------------------------------------------------------------------------*/

END_C_DECLS

#endif /* __CS_SYS_COUPLING_H__ */
