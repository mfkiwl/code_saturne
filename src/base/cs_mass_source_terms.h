#ifndef __CS_MASS_SOURCE_TERMS_H__
#define __CS_MASS_SOURCE_TERMS_H__

/*============================================================================
 * Mass source terms computation.
 *============================================================================*/

/*
  This file is part of Code_Saturne, a general-purpose CFD tool.

  Copyright (C) 1998-2020 EDF S.A.

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
 *  Local headers
 *----------------------------------------------------------------------------*/

#include "cs_base.h"

/*----------------------------------------------------------------------------*/

BEGIN_C_DECLS

/*=============================================================================
 * Public function prototypes
 *============================================================================*/

/*----------------------------------------------------------------------------*/
/*!
 * \brief Implicit and explicit mass source terms computation.
 *
 * \param[in]     ncesmp        number of cells with mass source term
 * \param[in]     iterns        iteration number on Navier-Stoke
 * \param[in]     icetsm        source mass cells pointer (1-based numbering)
 * \param[in]     itpsmp        mass source type for the working variable
 *                              (see \ref cs_user_mass_source_terms)
 * \param[in]     volume        cells volume
 * \param[in]     pvara         variable value at time step beginning
 * \param[in]     smcelp        value of the variable associated with mass source
 * \param[in]     gamma         flow mass value
 * \param[in,out] tsexp         explicit source term part linear in the variable
 * \param[in,out] tsimp         associated value with \c tsexp
 *                              to be stored in the matrix
 * \param[out]    gapinj        explicit source term part independant
 *                              of the variable
 */
/*----------------------------------------------------------------------------*/

void
cs_mass_source_terms(cs_lnum_t             ncesmp,
                     int                   iterns,
                     const int             icetsm[],
                     int                   itpsmp[],
                     const cs_real_t       volume[],
                     const cs_real_t       pvara[],
                     const cs_real_t       smcelp[],
                     const cs_real_t       gamma[],
                     cs_real_t             st_exp[],
                     cs_real_t             st_imp[],
                     cs_real_t             gapinj[]);

/*----------------------------------------------------------------------------*/

END_C_DECLS

#endif /* __CS_MASS_SOURCE_TERMS_H__ */
