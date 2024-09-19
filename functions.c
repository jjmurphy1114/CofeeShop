#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*
get_totals(int rows, int cols, int sales_data[][cols])
Creates a file with the sales data printed from the given array
Input:
    rows: number of rows in sales_data
    cols: number of columns in sales_data
    sales_data: 2D array of all sales for each item in the months given upon running the program
Output:
    File called "Total_sales.txt" with each item and the number of times it was sold
*/
void get_totals(int rows, int cols, int sales_data[][cols]){
    FILE* f1 = fopen("Total_sales.txt", "w");
    int tally;
    for (int row = 1; row < rows; row++){
        tally = 0;
        for (int col = 0; col < cols; col++){
            if (col == 0){
                fprintf(f1, "%2d", sales_data[row][0]);
            }else{
                tally += sales_data[row][col];
            }
        }
        fprintf(f1, "%6d\n", tally);
    }
    fclose(f1);
}

/*
get_profits(int rows, int cols, int sales_data[][cols], float costs[], float purch[])
Creates a file with the each items sales, cost, and revenue from the given array
Input:
    rows: number of rows in sales_data
    cols: number of columns in sales_data
    sales_data: 2D array of all sales for each item in the months given upon running the program
    costs[]: Array on the heap that contains the costs of manufacturing each item
    purch[]: Array on the heap that contains the sales of each item
Output:
    File called "Profits.txt" with each item and the number of times it was sold, total sales, total cost, and revenue
*/
void get_profits(int rows, int cols, int sales_data[][cols], float costs[], float purch[]){
    FILE* f1 = fopen("Profits.txt", "w");
    int tally;
    float cost, sales, revenue;
    fprintf(f1, "Item       #   Sales    Cost Revenue\n");
    for (int row = 1; row < rows; row++){
        int tally = 0;
        for(int col = 0; col < cols; col++){
            if (col == 0){
                fprintf(f1, "%4d", sales_data[row][0]);
            }else{
                tally += sales_data[row][col];
            }
        }
        sales = tally * purch[row];
        cost = tally * costs[row];
        revenue = sales - cost; 
        fprintf(f1, "%8d %7.2f %7.2f %7.2f\n", tally, sales, cost, revenue);
    }
    fclose(f1);
}

/*
top_earner(int rows, int cols, int sales_data[][cols], float costs[], float purch[])
Creates a file of the items with the top 10 revenues and the number of times they've been sold in the given array
Input:
    rows: number of rows in sales_data
    cols: number of columns in sales_data
    sales_data: 2D array of all sales for each item in the months given upon running the program
    costs[]: Array on the heap that contains the costs of manufacturing each item
    purch[]: Array on the heap that contains the sales of each item
Output:
    File called "Top_earners.txt" with the items with the top 10 revenues and the number of times they were sold
*/
void top_earner(int rows, int cols, int sales_data[][cols], float costs[], float purch[]){
    FILE* f1 = fopen("Top_earners.txt", "w");
    int count = 0;
    int tally;
    float sales, cost, revenue;
    float item_revenues[rows];
    int item_tallys[rows]; 
    float max_val;
    int max_row;
    //Initialize arrays to 0
    for (int row = 0; row < rows; row++){
        item_revenues[row] = 0;
        item_tallys[row] = 0;
    }
    fprintf(f1, "Item   #  Revenue\n");
    for (int row = 1; row < rows; row++){
        int tally = 0;
        for (int col = 1; col < cols; col++){
            tally += sales_data[row][col];
        }
        sales = tally * purch[row];
        cost = tally * costs[row];
        revenue = sales - cost;
        item_tallys[row] = tally;
        item_revenues[row] = revenue;       
    }    
    while (count < 10){
        max_val = 0.00;
        for (int row = 0; row < rows; row++){
            if (item_revenues[row] > max_val){
                max_val = item_revenues[row];
                max_row = row;
            }  
        }
        fprintf(f1, "%4d %3d %8.2f\n", max_row, item_tallys[max_row], item_revenues[max_row]);
        item_revenues[max_row] = 0.00;
        count++;
    }
    fclose(f1);
}

/*
    float* readCosts(int numItems)
    Creates an array on the heap of the costs of each item and returns the pointer to that array
    Input:
        numItems: Number of items to read
    Output:
        Pointer to the costs array on the heap

*/
float* readCosts(int numItems){
    FILE* f1 = fopen("Costs.txt", "r");\
    float cost = 0.0;
    float* costs = malloc(sizeof(float)*numItems);
    int i = 1;
    while (fscanf(f1, "%*d %*f %f", &cost) > 0){
        costs[i] = cost;
        i++;
    }
    fclose(f1);
    return costs;   
}

/*
    float* readPurch(int numItems)
    Creates an array on the heap of the sales of each item and returns the pointer to that array
    Input:
        numItems: Number of items to read
    Output:
        Pointer to the purch array on the heap

*/
float* readPurch(int numItems){
    FILE* f1 = fopen("Costs.txt", "r");\
    float purch = 0.0;
    float* purches = malloc(sizeof(float)*numItems);
    int i = 1;
    while (fscanf(f1, "%*d %f %*f", &purch) > 0){
        purches[i] = purch;
        i++;
    }
    fclose(f1);
    return purches;   
}