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
