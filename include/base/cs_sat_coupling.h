/*============================================================================
 *
 *     This file is part of the Code_Saturne Kernel, element of the
 *     Code_Saturne CFD tool.
 *
 *     Copyright (C) 1998-2009 EDF S.A., France
 *
 *     contact: saturne-support@edf.fr
 *
 *     The Code_Saturne Kernel is free software; you can redistribute it
 *     and/or modify it under the terms of the GNU General Public License
 *     as published by the Free Software Foundation; either version 2 of
 *     the License, or (at your option) any later version.
 *
 *     The Code_Saturne Kernel is distributed in the hope that it will be
 *     useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *     of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with the Code_Saturne Kernel; if not, write to the
 *     Free Software Foundation, Inc.,
 *     51 Franklin St, Fifth Floor,
 *     Boston, MA  02110-1301  USA
 *
 *============================================================================*/

#ifndef __CS_SAT_COUPLING_H__
#define __CS_SAT_COUPLING_H__

/*============================================================================
 * Functions associated with code coupling.
 *============================================================================*/

/*----------------------------------------------------------------------------
 * Standard C library headers
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Local headers
 *----------------------------------------------------------------------------*/

#include "cs_base.h"

/*----------------------------------------------------------------------------*/

BEGIN_C_DECLS

/*=============================================================================
 * Structure Definitions
 *============================================================================*/

typedef struct _cs_sat_coupling_t cs_sat_coupling_t;

/*============================================================================
 *  Public function prototypes for Fortran API
 *============================================================================*/

/*----------------------------------------------------------------------------
 * Define new Code_Saturne coupling.
 *
 * Fortran Interface:
 *
 * SUBROUTINE DEFSA1
 * *****************
 *
 * INTEGER        saturne_app_num   : <-- : application number of coupled
 *                                  :     : Code_Saturne instance, or -1
 * CHARACTER*     saturne_name      : <-- : name of coupled Code_Saturne instance
 * CHARACTER      projection_axis   : <-- : ' ' for 3D, 'x', 'y', or 'z'
 *                                  :     : for 2D projection
 * CHARACTER*     boundary_criteria : <-- : boundary face selection criteria,
 *                                  :     : empty if no boundary coupling
 * CHARACTER*     volume_criteria   : <-- : volume cell selection criteria,
 *                                  :     : empty if no volume coupling
 * INTEGER        verbosity         : <-- : verbosity level
 * INTEGER        saturne_n_len     : <-- : length of saturne_name
 * INTEGER        boundary_c_len    : <-- : length of boundary_criteria
 * INTEGER        volume_c_len      : <-- : length of volume_criteria
 *----------------------------------------------------------------------------*/

void CS_PROCF(defsa1, DEFSA1)
(
 cs_int_t    *saturne_app_num,
 const char  *saturne_name,
 const char  *boundary_cpl_criteria,
 const char  *volume_cpl_criteria,
 const char  *boundary_sup_criteria,
 const char  *volume_sup_criteria,
 cs_int_t    *verbosity,
 cs_int_t    *saturne_n_len,
 cs_int_t    *boundary_cpl_c_len,
 cs_int_t    *volume_cpl_c_len,
 cs_int_t    *boundary_sup_c_len,
 cs_int_t    *volume_sup_c_len
 CS_ARGF_SUPP_CHAINE
);

/*----------------------------------------------------------------------------
 * Get number of code coupling
 *
 * Fortran interface:
 *
 * SUBROUTINE NBCCPL
 * *****************
 *
 * INTEGER          NBRCPL         : <-- : number of code couplings
 *----------------------------------------------------------------------------*/

void CS_PROCF (nbccpl, NBCCPL)
(
 cs_int_t  *nbrcpl
);

/*----------------------------------------------------------------------------
 * Set the list of cells and boundary faces associated to a coupling
 * and a cloud of point.
 *
 * The local "support" cells and boundary faces are used to localize
 * the values in the distant "coupled" cells and faces.
 * Depending on the role of sender and/or receiver of the current process
 * in the coupling, some of these sets can be empty or not.
 *
 * The cell values are always localized and interpolated on the distant
 * "cells" support. The face values are localized and interpolated on
 * the distant "face" support if present, or on the distant "cell" support
 * if not.
 *
 * If the input arrays LCESUP and LFBSUP are not ordered, they will be
 * orderd in output.
 *
 * Fortran interface:
 *
 * SUBROUTINE DEFCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 *----------------------------------------------------------------------------*/

void CS_PROCF (defloc, DEFLOC)
(
 const cs_int_t  *numcpl
);

/*----------------------------------------------------------------------------
 * Get the number of cells and boundary faces, "support", coupled and not
 * localized associated to a given coupling
 *
 * Fortran interface:
 *
 * SUBROUTINE NBECPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NCESUP         : <-- : number of "support" cells
 * INTEGER          NFBSUP         : <-- : number of "support" boundary faces
 * INTEGER          NCECPL         : <-- : number of coupled cells
 * INTEGER          NFBCPL         : <-- : number of coupled boundary faces
 * INTEGER          NCENCP         : <-- : number of not coupled cells
 *                                 :     : (since not localized)
 * INTEGER          NFBNCP         : <-- : number of not coupled boundary faces
 *                                 :     : (since not localized)
 *----------------------------------------------------------------------------*/

void CS_PROCF (nbecpl, NBECPL)
(
 const cs_int_t  *numcpl,
       cs_int_t  *ncesup,
       cs_int_t  *nfbsup,
       cs_int_t  *ncecpl,
       cs_int_t  *nfbcpl,
       cs_int_t  *ncencp,
       cs_int_t  *nfbncp
);

/*----------------------------------------------------------------------------
 * Get the lists of coupled cells and boundary faces (i.e. receiving)
 * associated to a given coupling
 *
 * The number of cells and boundary faces, got with NBECPL(), are used
 * for arguments coherency checks.
 *
 * Fortran interface:
 *
 * SUBROUTINE LELCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NCECPL         : --> : number of coupled cells
 * INTEGER          NFBCPL         : --> : number of coupled boundary faces
 * INTEGER          LCECPL(*)      : <-- : list of coupled cells
 * INTEGER          LFBCPL(*)      : <-- : list of coupled boundary faces
 *----------------------------------------------------------------------------*/

void CS_PROCF (lelcpl, LELCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *ncecpl,
 const cs_int_t  *nfbcpl,
       cs_int_t  *lcecpl,
       cs_int_t  *lfbcpl
);

/*----------------------------------------------------------------------------
 * Get the lists of not coupled cells and boundary faces (i.e. receiving but
 * not localized) associated to a given coupling
 *
 * The number of cells and boundary faces, got with NBECPL(), are used
 * for arguments coherency checks.
 *
 * Fortran interface:
 *
 * SUBROUTINE LENCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NCENCP         : --> : number of not coupled cells
 * INTEGER          NFBNCP         : --> : number of not coupled boundary faces
 * INTEGER          LCENCP(*)      : <-- : list of not coupled cells
 * INTEGER          LFBNCP(*)      : <-- : list of not coupled boundary faces
 *----------------------------------------------------------------------------*/

void CS_PROCF (lencpl, LENCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *ncencp,
 const cs_int_t  *nfbncp,
       cs_int_t  *lcencp,
       cs_int_t  *lfbncp
);

/*----------------------------------------------------------------------------
 * Get the number of distant point associated to a given coupling
 * and localized on the local domain
 *
 * Fortran interface:
 *
 * SUBROUTINE NPDCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NCEDIS         : <-- : number of distant cells
 * INTEGER          NFBDIS         : <-- : numbre de distant boundary faces
 *----------------------------------------------------------------------------*/

void CS_PROCF (npdcpl, NPDCPL)
(
 const cs_int_t  *numcpl,
       cs_int_t  *ncedis,
       cs_int_t  *nfbdis
);

/*----------------------------------------------------------------------------
 * Get the distant points coordinates associated to a given coupling
 * and a list of points, and the elements number and type (cell or face)
 * "containing" this points.
 *
 * The number of distant points NBRPTS must be equal to one the arguments
 * NCEDIS or NFBDIS given by NPDCPL(), and is given here for coherency checks
 * between the arguments NUMCPL and ITYSUP.
 *
 * Fortran interface:
 *
 * SUBROUTINE COOCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NBRPTS         : --> : number of distant points
 * INTEGER          ITYDIS         : --> : 1 : access to the points associated
 *                                 :     :     to the distant cells
 *                                 :     : 2 : access to the points associated
 *                                 :     :     to the distant boundary faces
 * INTEGER          ITYLOC         : <-- : 1 : localization on the local cells
 *                                 :     : 2 : localization on the local faces
 * INTEGER          LOCPTS(*)      : <-- : "containing" number associated to
 *                                 :     :   each point
 * DOUBLE PRECISION COOPTS(3,*)    : <-- : distant point coordinates
 *----------------------------------------------------------------------------*/

void CS_PROCF (coocpl, COOCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *nbrpts,
 const cs_int_t  *itydis,
       cs_int_t  *ityloc,
       cs_int_t  *locpts,
       cs_real_t *coopts,
       cs_real_t *djppts,
       cs_real_t *dofpts,
       cs_real_t *pndpts
);

/*----------------------------------------------------------------------------
 * Get the weighting coefficient needed for a centred-like interpolation
 * in the case of a coupling on boundary faces.
 *
 * Fortran interface:
 *
 * SUBROUTINE PNDCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NBRCPL         : --> : number of distant points
 * INTEGER          ITYLOC         : <-- : 1 : localization on the local cells
 *                                 :     : 2 : localization on the local faces
 * DOUBLE PRECISION PONDCP(*)      : <-- : weighting coefficients
 *----------------------------------------------------------------------------*/

void CS_PROCF (pndcpl, PNDCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *nbrcpl,
       cs_int_t  *ityloc,
       cs_real_t *pondcp,
       cs_real_t *distof
);

/*----------------------------------------------------------------------------
 * Exchange a variable associated to a set of point and a coupling.
 *
 * Fortran interface:
 *
 * SUBROUTINE VARCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NBRDIS         : --> : number of values to send
 * INTEGER          NBRLOC         : --> : number of values to receive
 * INTEGER          ITYVAR         : --> : 1 : variables defined at cells
 *                                 :     : 2 : variables defined at faces
 * DOUBLE PRECISION VARDIS(*)      : --> : distant variable(to send)
 * DOUBLE PRECISION VARLOC(*)      : <-- : local variable (to receive)
 *----------------------------------------------------------------------------*/

void CS_PROCF (varcpl, VARCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *nbrdis,
 const cs_int_t  *nbrloc,
 const cs_int_t  *ityvar,
       cs_real_t *vardis,
       cs_real_t *varloc
);

/*----------------------------------------------------------------------------
 * Array of integers exchange, associated to a given coupling.
 *
 * It is assumed that the arrays have the same size and the same values on
 * each group of processus (local and distant).
 *
 * Fortran interface:
 *
 * SUBROUTINE TBICPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NBRDIS         : --> : number of values to send
 * INTEGER          NBRLOC         : --> : number of values to receive
 * INTEGER          TABDIS(*)      : --> : distant values (to send)
 * INTEGER          TABLOC(*)      : <-- : local values (to receive)
 *----------------------------------------------------------------------------*/

void CS_PROCF (tbicpl, TBICPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *nbrdis,
 const cs_int_t  *nbrloc,
       cs_int_t  *vardis,
       cs_int_t  *varloc
);


/*----------------------------------------------------------------------------
 * Array of reals exchange, associated to a given coupling.
 *
 * It is assumed that the arrays have the same size and the same values on
 * each group of processus (local and distant).
 *
 * Fortran interface:
 *
 * SUBROUTINE TBRCPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          NBRDIS         : --> : number of values to send
 * INTEGER          NBRLOC         : --> : number of values to receive
 * DOUBLE PRECISION TABDIS(*)      : --> : distant values (to send)
 * DOUBLE PRECISION TABLOC(*)      : <-- : local values (to receive)
 *----------------------------------------------------------------------------*/

void CS_PROCF (tbrcpl, TBRCPL)
(
 const cs_int_t  *numcpl,
 const cs_int_t  *nbrdis,
 const cs_int_t  *nbrloc,
       cs_real_t *vardis,
       cs_real_t *varloc
);

/*----------------------------------------------------------------------------
 * Compute the maximum value of an integer variable associated to a coupling.
 *
 * It is assumed that the integer value is the same for each group of
 * processus (local and distant).
 *
 * Fortran interface:
 *
 * SUBROUTINE MXICPL
 * *****************
 *
 * INTEGER          NUMCPL         : --> : coupling number
 * INTEGER          VALDIS         : --> : distant value (to send)
 * INTEGER          VALMAX         : <-- : local maximum (to receive)
 *----------------------------------------------------------------------------*/

void CS_PROCF (mxicpl, MXICPL)
(
 const cs_int_t  *const numcpl,
       cs_int_t  *const vardis,
       cs_int_t  *const varmax
);

/*============================================================================
 * Public function definitions
 *============================================================================*/

/*----------------------------------------------------------------------------
 * Define new Code_Saturne coupling.
 *
 * arguments:
 *   saturne_app_num   <-- number of Code_Saturne application, or -1
 *   saturne_name      <-- name of Code_Saturne instance, or NULL
 *   boundary_criteria <-- boundary face selection criteria, or NULL
 *   volume_criteria   <-- volume cell selection criteria, or NULL
 *   verbosity         <-- verbosity level
 *----------------------------------------------------------------------------*/

void
cs_sat_coupling_define(int          saturne_app_num,
                       const char  *saturne_name,
                       const char  *boundary_cpl_criteria,
                       const char  *volume_cpl_criteria,
                       const char  *boundary_sup_criteria,
                       const char  *volume_sup_criteria,
                       int          verbosity);

/*----------------------------------------------------------------------------
 * Get number of Code_Saturne couplings.
 *
 * returns:
 *   number of Code_Saturne couplings
 *----------------------------------------------------------------------------*/

fvm_lnum_t
cs_sat_coupling_n_couplings(void);

/*----------------------------------------------------------------------------
 * Get pointer to Code_Saturne coupling.
 *
 * parameters:
 *   coupling_id <-- Id (0 to n-1) of Code_Saturne coupling
 *
 * returns:
 *   pointer to Code_Saturne coupling structure
 *----------------------------------------------------------------------------*/

cs_sat_coupling_t *
cs_sat_coupling_by_id(fvm_lnum_t coupling_id);

/*----------------------------------------------------------------------------
 * Create a sat_coupling_t structure.
 *
 * parameters:
 *   ref_axis           <-- reference axis
 *   face_sel_criterion <-- criterion for selection of boundary faces
 *   cell_sel_criterion <-- criterion for selection of cells
 *   syr_num            <-- SYRTHES application number, or -1
 *   sat_name           <-- SYRTHES application name, or NULL
 *   verbosity          <-- verbosity level
 *----------------------------------------------------------------------------*/

void
cs_sat_coupling_add(const char  *face_cpl_sel_c,
                    const char  *cell_cpl_sel_c,
                    const char  *face_sup_sel_c,
                    const char  *cell_sup_sel_c,
                    int          sat_num,
                    const char  *sat_name,
                    int          verbosity);

/*----------------------------------------------------------------------------
 * Initialize Code_Saturne couplings.
 *
 * This function may be called once all couplings have been defined,
 * and it will match defined couplings with available applications.
 *----------------------------------------------------------------------------*/

void
cs_sat_coupling_all_init(void);

/*----------------------------------------------------------------------------
 * Destroy all couplings
 *----------------------------------------------------------------------------*/

void
cs_sat_coupling_all_finalize(void);

/*----------------------------------------------------------------------------*/

END_C_DECLS

#endif /* __CS_COUPLAGE_H__ */
