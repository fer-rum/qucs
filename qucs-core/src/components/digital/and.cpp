/*
 * and.cpp - logical and class implementation
 *
 * Copyright (C) 2005 Stefan Jahn <stefan@lkcc.org>
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this package; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.  
 *
 * $Id: and.cpp,v 1.3 2005/12/05 07:04:57 margraf Exp $
 *
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>

#include "complex.h"
#include "object.h"
#include "circuit.h"
#include "component_id.h"
#include "constants.h"
#include "digital.h"
#include "and.h"

logicand::logicand () : digital () {
  type = CIR_AND;
  setVariableSized (true);
}

void logicand::calcOutput (void) {
  nr_double_t v = getPropertyDouble ("V");
  nr_double_t n = getSize () - 1;
  nr_double_t x;
  for (x = 0, i = 0; i < n; i++) {
    x += 2 / (1 + calcTransfer (i));
  }
  Vout = v * n / x;
}

void logicand::calcDerivatives (void) {
  nr_double_t n = getSize () - 1;
  nr_double_t x;
  for (int k = 0; k < n; k++) {
    for (x = 0, i = 0; i < n; i++) {
      x += 2 / (1 + calcTransfer (i));
    }
    x *= (1 + calcTransfer (k));
    g[k] = n * calcDerivative (k) / x / x + GMin;
  }
}