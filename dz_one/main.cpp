#include <stdio.h>
#include <iostream>
#include "function.h"

int main() 
{

    int x = 0;
    
    while(1) 
    {
        printf("Enter 1 to check if point is in circle, 2 to check if point is in square, 3 to exit: ");
        std::cin >> x;

        switch(x) {
            case 1:
                printf("Enter x coordinate of the point: ");            
                std::cin >> coord_x;
                printf("Enter y coordinate of the point: ");            
                std::cin >> coord_y;
                if (is_in_circle(&coord_x, &coord_y, radius))
                {
                    printf("Point is in circle\n");
                }
                else
                {
                    printf("Point is not in circle\n");
                }
                break;
            case 2:
                
                printf("Enter x coordinate of the point: ");            
                std::cin >> coord_x;
                printf("Enter y coordinate of the point: ");            
                std::cin >> coord_y;
                if (is_in_square(&coord_x, &coord_y, side_length))
                {
                    printf("Point is in square\n");
                }
                else
                {
                    printf("Point is not in square\n"); 
                }
                break;
            case 3:
                printf("Exiting program\n");
                return 0;
            default:
                printf("Invalid switch value\n");
        }
    }

    return 0;
}
