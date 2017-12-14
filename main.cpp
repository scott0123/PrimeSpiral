#include <iostream>
#include "../PNG/png.h"
#include <cmath>

using namespace std;

void move_direction(int dir, int &x, int &y);
bool isPrime(int n);

int main(){

    int input;
    cout << "Please enter the number of steps in the prime spiral:" << endl;
    cin >> input;

    int steps = input;
    
    // figure out the corresponding side length for png file
    int side = ceil(sqrt(steps));
    // it needs to be odd for 1 to be in the center
    if(side % 2 == 0) side++;

    // create the png on the heap
    PNG* image = new PNG(side, side);

    // the 0, 0 of the image is actually in the middle
    int zero = side / 2;


    // --- from advent day 3 (modified) ---
    // starting direction is right
    int dir = 0;
    // steps per change in direction
    int step_limit = 1;
    int step_counter = 0;
    int new_limit_reached_count = 0;

    // x > 0 for right, y > 0 for up
    int x = 0;
    int y = 0;

    // do the following process "steps" times
    for(int i = 1; i < steps + 1; i++){

        // color the square green if prime, otherwise color it light grey
        RGBAPixel* curr = (*image)(zero + x, zero - y);
        if(isPrime(i)){
            curr->red = 0;
            curr->green = 100;
            curr->blue = 0;
            //cout << i << " at (" << x << ", " << y << ") is a prime" << endl;
        } else {
            curr->red = 240;
            curr->green = 240;
            curr->blue = 240;
            //cout << i << " at (" << x << ", " << y << ") is not a prime" << endl;
        }
        // start moving
        dir %= 4;
        move_direction(dir, x, y);

        // for the next step
        step_counter++;
        if(step_counter < step_limit){
        } else {
            // reset counter
            step_counter = 0;
            dir++;
            new_limit_reached_count++;
            // change step limit every two times the limit is hit
            if(new_limit_reached_count >= 2){
                new_limit_reached_count = 0;
                step_limit++;
            }
        }
    }
    // --- end of advent day 3 ---

    // color (zero, zero) red
    RGBAPixel* mid = (*image)(zero, zero);
    mid->red = 200;
    mid->green = 0;
    mid->blue = 0;

    // generating output
    cout << "Generating output..." << endl;
    if(image->writeToFile("output.png")){
        cout << "Success!" << endl;
    } else {
        cout << "Failure." << endl;
    }
    cout << "Attempting to free heap..." << endl;
    int image_size = sizeof(PNG) + side * side * sizeof(RGBAPixel);
    delete image;
    cout << image_size << " bytes successfully freed." << endl;
    return 1;
}

void move_direction(int dir, int &x, int &y){

    // right = 0, up = 1, left = 2, down = 3
    switch(dir){
    case 0:
        x++;
        //cout << "Moving right" << endl;
        break;
    case 1:
        y++;
        //cout << "Moving up" << endl;
        break;
    case 2:
        x--;
        //cout << "Moving left" << endl;
        break;
    case 3:
        y--;
        //cout << "Moving down" << endl;
        break;
    default:
        cout << "Something went wrong in move_direction" << endl;
    }
}

bool isPrime(int n){
    
    if(n < 2){
        return false;
    }
    
    for(int i = 2; i*i <= n; i++){
        if(n % i == 0){
            return false;
        }
    }
    // if at this point its still not divisible, its a prime
    return true;
}
