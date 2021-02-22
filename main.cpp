/*
Pico Traffic Signals
Copyright (C) 2021  goballstate at gmail

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "signal.h"
#include "intersection.h"

int main()
{
    bi_decl(bi_program_description("Control common anode automobile traffic signals using a Pico"));

    stdio_init_all();

    Signal primary(20, 18, 16);
    Signal opposed(28, 27, 26);
    Intersection intersection(&primary, &opposed);

    intersection.run();
}
