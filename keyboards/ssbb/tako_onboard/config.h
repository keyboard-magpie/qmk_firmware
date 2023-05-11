/* Copyright 2023 ssbb
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#define MATRIX_ROWS 4
#define MATRIX_COLS 10

// #define DIODE_DIRECTION COL2ROW

/* Custom matrix pins and port select array */
#define MATRIX_ROW_PINS \
    { A14, A15, B4, B5 }
#define MATRIX_COL_CHANNELS \
    { 4, 3, 2, 1, 0}
#define MUX_SEL_PINS \
    { A4, A5, A6 }

/* Hardware peripherals pins */
#define APLEX_EN_PIN A7
#define DISCHARGE_PIN A3
#define ANALOG_PORT A2

#define DEFAULT_ACTUATION_LEVEL 700
#define DEFAULT_RELEASE_LEVEL 650

#define DISCHARGE_TIME 10
