#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
    #define CLEAR_SCREEN() system("cls")
    #define SET_COLOR(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color)
#else
    #include <unistd.h>
    #define CLEAR_SCREEN() system("clear")
    #define SET_COLOR(color) printf("\033[%dm", color)
#endif

// Color definitions
#define RESET_COLOR() SET_COLOR(7)
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14
#define COLOR_BLUE 9
#define COLOR_MAGENTA 13
#define COLOR_CYAN 11
#define COLOR_WHITE 15
#define COLOR_BRIGHT_RED 12
#define COLOR_BRIGHT_GREEN 10
#define COLOR_BRIGHT_YELLOW 14
#define COLOR_BRIGHT_BLUE 9
#define COLOR_BRIGHT_MAGENTA 13
#define COLOR_BRIGHT_CYAN 11

// Maximum limits
#define MAX_PRODUCTS 1000
#define MAX_NAME_LEN 100
#define MAX_CATEGORY_LEN 50
#define MAX_SUPPLIER_LEN 100
#define FILENAME "inventory.dat"

// Product structure
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char category[MAX_CATEGORY_LEN];
    int quantity;
    double price;
    double cost_price;
    char supplier[MAX_SUPPLIER_LEN];
    time_t added_date;
    time_t last_updated;
    int reorder_level;
    int sold_count;
} Product;

// Global variables
Product products[MAX_PRODUCTS];
int product_count = 0;
int current_color_index = 0;
const int colors[] = {COLOR_CYAN, COLOR_GREEN, COLOR_YELLOW, COLOR_MAGENTA, COLOR_BLUE, COLOR_RED};

// Function prototypes
void load_data();
void save_data();
void display_menu();
void add_product();
void update_product();
void delete_product();
void search_products();
void stock_management();
void sales_report();
void sort_products();
void binary_search_product();
void display_product(Product *p);
void display_products();
void generate_low_stock_report();
void generate_category_report();
void generate_supplier_report();
void set_screen_color();
void print_header(const char *title);
void print_separator();
void wait_for_enter();
int get_valid_int(const char *prompt, int min, int max);
double get_valid_double(const char *prompt, double min, double max);
void to_lowercase(char *str);
int compare_by_name(const void *a, const void *b);
int compare_by_price(const void *a, const void *b);
int compare_by_quantity(const void *a, const void *b);
int compare_by_category(const void *a, const void *b);

// Main function
int main() {
    load_data();

    int choice;
    do {
        set_screen_color();
        display_menu();
        choice = get_valid_int("Enter your choice (0-12): ", 0, 12);

        switch(choice) {
            case 1: add_product(); break;
            case 2: update_product(); break;
            case 3: delete_product(); break;
            case 4: search_products(); break;
            case 5: stock_management(); break;
            case 6: sales_report(); break;
            case 7: sort_products(); break;
            case 8: binary_search_product(); break;
            case 9: display_products(); break;
            case 10: generate_low_stock_report(); break;
            case 11: generate_category_report(); break;
            case 12: generate_supplier_report(); break;
            case 0:
                SET_COLOR(COLOR_BRIGHT_YELLOW);
                printf("\n  Saving data...\n");
                save_data();
                SET_COLOR(COLOR_BRIGHT_GREEN);
                printf("  Thank you for using Inventory System!\n");
                RESET_COLOR();
                break;
        }
    } while(choice != 0);

    return 0;
}

// Load data from file
void load_data() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        product_count = 0;
        return;
    }

    fread(&product_count, sizeof(int), 1, file);
    fread(products, sizeof(Product), product_count, file);
    fclose(file);
}

// Save data to file
void save_data() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        SET_COLOR(COLOR_RED);
        printf("\n  Error: Cannot save data!\n");
        RESET_COLOR();
        return;
    }

    fwrite(&product_count, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), product_count, file);
    fclose(file);
}

// Set screen color based on menu option
void set_screen_color() {
    current_color_index = (current_color_index + 1) % (sizeof(colors) / sizeof(colors[0]));
    SET_COLOR(colors[current_color_index]);
}

// Print header with styling
void print_header(const char *title) {
    SET_COLOR(COLOR_WHITE);
    printf("\n+==================================================+\n");
    SET_COLOR(COLOR_BRIGHT_YELLOW);
    printf("|                    %-40s |\n", title);
    SET_COLOR(COLOR_WHITE);
    printf("+==================================================+\n");
    RESET_COLOR();
}

// Print separator
void print_separator() {
    SET_COLOR(COLOR_WHITE);
    printf("----------------------------------------------------\n");
    RESET_COLOR();
}

// Wait for enter key
void wait_for_enter() {
    SET_COLOR(COLOR_CYAN);
    printf("\n  Press Enter to continue...");
    RESET_COLOR();
    getchar();
    getchar();
}

// Get valid integer input
int get_valid_int(const char *prompt, int min, int max) {
    int value;
    char input[100];
    while (1) {
        SET_COLOR(COLOR_BRIGHT_CYAN);
        printf("%s", prompt);
        RESET_COLOR();
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        SET_COLOR(COLOR_RED);
        printf("  Invalid input! Please enter a number between %d and %d.\n", min, max);
        RESET_COLOR();
    }
}

// Get valid double input
double get_valid_double(const char *prompt, double min, double max) {
    double value;
    char input[100];
    while (1) {
        SET_COLOR(COLOR_BRIGHT_CYAN);
        printf("%s", prompt);
        RESET_COLOR();
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%lf", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        SET_COLOR(COLOR_RED);
        printf("  Invalid input! Please enter a number between %.2f and %.2f.\n", min, max);
        RESET_COLOR();
    }
}

// Convert string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Display main menu
void display_menu() {
    CLEAR_SCREEN();
    print_header("INVENTORY MANAGEMENT SYSTEM");

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  MAIN MENU\n");
    print_separator();

    SET_COLOR(COLOR_GREEN);
    printf("  %2d. Add Product\n", 1);
    printf("  %2d. Update Product\n", 2);
    printf("  %2d. Delete Product\n", 3);
    printf("  %2d. Search Products\n", 4);
    printf("  %2d. Stock Management\n", 5);
    printf("  %2d. Sales Report\n", 6);
    printf("  %2d. Sort Products\n", 7);
    printf("  %2d. Binary Search\n", 8);
    printf("  %2d. View All Products\n", 9);
    printf("  %2d. Low Stock Report\n", 10);
    printf("  %2d. Category Report\n", 11);
    printf("  %2d. Supplier Report\n", 12);
    SET_COLOR(COLOR_RED);
    printf("  %2d. Exit\n", 0);

    RESET_COLOR();
    print_separator();
    SET_COLOR(COLOR_BRIGHT_YELLOW);
    printf("  Total Products: %d\n", product_count);
    RESET_COLOR();
}

// Display a single product
void display_product(Product *p) {
    SET_COLOR(COLOR_WHITE);
    printf("  +-----------------------------------------------+\n");
    SET_COLOR(COLOR_BRIGHT_YELLOW);
    printf("  | ID: %-6d | Qty: %-6d | Sold: %-6d |\n", p->id, p->quantity, p->sold_count);
    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  | Name: %-20s | Category: %-15s |\n", p->name, p->category);
    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("  | Price: $%-10.2f | Cost: $%-10.2f |\n", p->price, p->cost_price);
    SET_COLOR(COLOR_BRIGHT_MAGENTA);
    printf("  | Supplier: %-20s | Reorder: %-6d |\n", p->supplier, p->reorder_level);
    SET_COLOR(COLOR_WHITE);
    printf("  +-----------------------------------------------+\n");
    RESET_COLOR();
}

// Display all products
void display_products() {
    CLEAR_SCREEN();
    print_header("ALL PRODUCTS");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    for (int i = 0; i < product_count; i++) {
        display_product(&products[i]);
        printf("\n");
    }

    wait_for_enter();
}

// Add product
void add_product() {
    CLEAR_SCREEN();
    print_header("ADD NEW PRODUCT");

    if (product_count >= MAX_PRODUCTS) {
        SET_COLOR(COLOR_RED);
        printf("\n  Inventory is full! Cannot add more products.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    Product new_product;
    memset(&new_product, 0, sizeof(Product));

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Enter Product Details:\n");
    print_separator();

    new_product.id = product_count + 1001;

    SET_COLOR(COLOR_WHITE);
    printf("  Product ID: %d (Auto-generated)\n", new_product.id);

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  Product Name: ");
    RESET_COLOR();
    fgets(new_product.name, MAX_NAME_LEN, stdin);
    new_product.name[strcspn(new_product.name, "\n")] = 0;

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  Category: ");
    RESET_COLOR();
    fgets(new_product.category, MAX_CATEGORY_LEN, stdin);
    new_product.category[strcspn(new_product.category, "\n")] = 0;

    new_product.quantity = get_valid_int("  Quantity: ", 0, 999999);
    new_product.price = get_valid_double("  Selling Price ($): ", 0, 999999.99);
    new_product.cost_price = get_valid_double("  Cost Price ($): ", 0, 999999.99);

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  Supplier: ");
    RESET_COLOR();
    fgets(new_product.supplier, MAX_SUPPLIER_LEN, stdin);
    new_product.supplier[strcspn(new_product.supplier, "\n")] = 0;

    new_product.reorder_level = get_valid_int("  Reorder Level: ", 0, 999999);
    new_product.added_date = time(NULL);
    new_product.last_updated = time(NULL);
    new_product.sold_count = 0;

    products[product_count++] = new_product;
    save_data();

    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("\n  Product added successfully!\n");
    printf("  Total products: %d\n", product_count);
    RESET_COLOR();

    wait_for_enter();
}

// Update product
void update_product() {
    CLEAR_SCREEN();
    print_header("UPDATE PRODUCT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available to update.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    display_products();

    int id = get_valid_int("\n  Enter Product ID to update: ", 1001, 9999);
    int index = -1;

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        SET_COLOR(COLOR_RED);
        printf("\n  Product with ID %d not found!\n", id);
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("\n  Current Product Details:\n");
    RESET_COLOR();
    display_product(&products[index]);

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Enter new details (press Enter to keep current value):\n");
    print_separator();

    char buffer[100];

    printf("  Product Name [%s]: ", products[index].name);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(products[index].name, buffer);

    printf("  Category [%s]: ", products[index].category);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(products[index].category, buffer);

    printf("  Quantity [%d]: ", products[index].quantity);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        int val;
        sscanf(buffer, "%d", &val);
        if (val >= 0) products[index].quantity = val;
    }

    printf("  Price [%.2f]: ", products[index].price);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        double val;
        sscanf(buffer, "%lf", &val);
        if (val >= 0) products[index].price = val;
    }

    printf("  Cost Price [%.2f]: ", products[index].cost_price);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        double val;
        sscanf(buffer, "%lf", &val);
        if (val >= 0) products[index].cost_price = val;
    }

    printf("  Supplier [%s]: ", products[index].supplier);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(products[index].supplier, buffer);

    printf("  Reorder Level [%d]: ", products[index].reorder_level);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        int val;
        sscanf(buffer, "%d", &val);
        if (val >= 0) products[index].reorder_level = val;
    }

    products[index].last_updated = time(NULL);
    save_data();

    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("\n  Product updated successfully!\n");
    RESET_COLOR();
    wait_for_enter();
}

// Delete product
void delete_product() {
    CLEAR_SCREEN();
    print_header("DELETE PRODUCT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available to delete.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    display_products();

    int id = get_valid_int("\n  Enter Product ID to delete: ", 1001, 9999);
    int index = -1;

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        SET_COLOR(COLOR_RED);
        printf("\n  Product with ID %d not found!\n", id);
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_RED);
    printf("\n  Are you sure you want to delete this product?\n");
    RESET_COLOR();
    display_product(&products[index]);

    int confirm = get_valid_int("\n  Enter 1 to confirm deletion, 0 to cancel: ", 0, 1);

    if (confirm == 1) {
        for (int i = index; i < product_count - 1; i++) {
            products[i] = products[i + 1];
        }
        product_count--;
        save_data();

        SET_COLOR(COLOR_BRIGHT_GREEN);
        printf("\n  Product deleted successfully!\n");
        RESET_COLOR();
    } else {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  Deletion cancelled.\n");
        RESET_COLOR();
    }

    wait_for_enter();
}

// Search products
void search_products() {
    CLEAR_SCREEN();
    print_header("SEARCH PRODUCTS");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available to search.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Search by:\n");
    printf("  1. Name\n");
    printf("  2. Category\n");
    printf("  3. Supplier\n");
    RESET_COLOR();

    int choice = get_valid_int("  Enter choice (1-3): ", 1, 3);
    char search_term[100];
    int found = 0;

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  Enter search term: ");
    RESET_COLOR();
    fgets(search_term, sizeof(search_term), stdin);
    search_term[strcspn(search_term, "\n")] = 0;

    char search_lower[100];
    strcpy(search_lower, search_term);
    to_lowercase(search_lower);

    CLEAR_SCREEN();
    print_header("SEARCH RESULTS");

    for (int i = 0; i < product_count; i++) {
        char compare_lower[100];
        int match = 0;

        switch(choice) {
            case 1:
                strcpy(compare_lower, products[i].name);
                to_lowercase(compare_lower);
                if (strstr(compare_lower, search_lower) != NULL) match = 1;
                break;
            case 2:
                strcpy(compare_lower, products[i].category);
                to_lowercase(compare_lower);
                if (strstr(compare_lower, search_lower) != NULL) match = 1;
                break;
            case 3:
                strcpy(compare_lower, products[i].supplier);
                to_lowercase(compare_lower);
                if (strstr(compare_lower, search_lower) != NULL) match = 1;
                break;
        }

        if (match) {
            display_product(&products[i]);
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products found matching '%s'\n", search_term);
        RESET_COLOR();
    } else {
        SET_COLOR(COLOR_BRIGHT_GREEN);
        printf("\n  Found %d product(s) matching '%s'\n", found, search_term);
        RESET_COLOR();
    }

    wait_for_enter();
}

// Stock management
void stock_management() {
    CLEAR_SCREEN();
    print_header("STOCK MANAGEMENT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    display_products();

    int id = get_valid_int("\n  Enter Product ID for stock adjustment: ", 1001, 9999);
    int index = -1;

    for (int i = 0; i < product_count; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        SET_COLOR(COLOR_RED);
        printf("\n  Product with ID %d not found!\n", id);
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Current Stock: %d\n", products[index].quantity);
    printf("  Reorder Level: %d\n", products[index].reorder_level);
    RESET_COLOR();
    display_product(&products[index]);

    int new_qty = get_valid_int("\n  Enter new quantity: ", 0, 999999);
    int difference = new_qty - products[index].quantity;

    products[index].quantity = new_qty;
    products[index].last_updated = time(NULL);

    if (difference > 0) {
        SET_COLOR(COLOR_BRIGHT_GREEN);
        printf("  Added %d units to stock.\n", difference);
    } else if (difference < 0) {
        SET_COLOR(COLOR_BRIGHT_RED);
        printf("  Removed %d units from stock.\n", -difference);
    } else {
        SET_COLOR(COLOR_YELLOW);
        printf("  No change in quantity.\n");
    }

    if (products[index].quantity <= products[index].reorder_level) {
        SET_COLOR(COLOR_BRIGHT_RED);
        printf("  WARNING: Stock is at or below reorder level!\n");
        RESET_COLOR();
    }

    save_data();
    RESET_COLOR();
    wait_for_enter();
}

// Sales report
void sales_report() {
    CLEAR_SCREEN();
    print_header("SALES REPORT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    double total_revenue = 0;
    double total_cost = 0;
    double total_profit = 0;
    int total_items_sold = 0;

    SET_COLOR(COLOR_WHITE);
    printf("\n  Sales Summary\n");
    print_separator();
    RESET_COLOR();

    for (int i = 0; i < product_count; i++) {
        double revenue = products[i].sold_count * products[i].price;
        double cost = products[i].sold_count * products[i].cost_price;
        double profit = revenue - cost;

        total_revenue += revenue;
        total_cost += cost;
        total_profit += profit;
        total_items_sold += products[i].sold_count;

        SET_COLOR(COLOR_CYAN);
        printf("  %-20s | Sold: %-6d | Revenue: $%-10.2f | Profit: $%-10.2f\n",
               products[i].name, products[i].sold_count, revenue, profit);
        RESET_COLOR();
    }

    print_separator();
    SET_COLOR(COLOR_BRIGHT_YELLOW);
    printf("  Total Items Sold: %d\n", total_items_sold);
    printf("  Total Revenue: $%.2f\n", total_revenue);
    printf("  Total Cost: $%.2f\n", total_cost);
    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("  Total Profit: $%.2f\n", total_profit);
    printf("  Profit Margin: %.2f%%\n", (total_revenue > 0) ? (total_profit / total_revenue * 100) : 0);
    RESET_COLOR();

    wait_for_enter();
}

// Sort products
void sort_products() {
    CLEAR_SCREEN();
    print_header("SORT PRODUCTS");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available to sort.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Sort by:\n");
    printf("  1. Name\n");
    printf("  2. Price\n");
    printf("  3. Quantity\n");
    printf("  4. Category\n");
    RESET_COLOR();

    int choice = get_valid_int("  Enter choice (1-4): ", 1, 4);

    switch(choice) {
        case 1: qsort(products, product_count, sizeof(Product), compare_by_name); break;
        case 2: qsort(products, product_count, sizeof(Product), compare_by_price); break;
        case 3: qsort(products, product_count, sizeof(Product), compare_by_quantity); break;
        case 4: qsort(products, product_count, sizeof(Product), compare_by_category); break;
    }

    save_data();

    SET_COLOR(COLOR_BRIGHT_GREEN);
    printf("\n  Products sorted successfully!\n");
    RESET_COLOR();

    display_products();
}

// Comparison functions for sorting
int compare_by_name(const void *a, const void *b) {
    return strcmp(((Product*)a)->name, ((Product*)b)->name);
}

int compare_by_price(const void *a, const void *b) {
    if (((Product*)a)->price < ((Product*)b)->price) return -1;
    if (((Product*)a)->price > ((Product*)b)->price) return 1;
    return 0;
}

int compare_by_quantity(const void *a, const void *b) {
    return ((Product*)a)->quantity - ((Product*)b)->quantity;
}

int compare_by_category(const void *a, const void *b) {
    return strcmp(((Product*)a)->category, ((Product*)b)->category);
}

// Binary search
void binary_search_product() {
    CLEAR_SCREEN();
    print_header("BINARY SEARCH");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("\n  Binary search requires sorted data.\n");
    printf("  Sorting products by name for search...\n");
    RESET_COLOR();

    qsort(products, product_count, sizeof(Product), compare_by_name);
    save_data();

    char search_name[100];
    SET_COLOR(COLOR_BRIGHT_CYAN);
    printf("  Enter product name to search: ");
    RESET_COLOR();
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    // Binary search implementation
    int left = 0, right = product_count - 1;
    int found_index = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(products[mid].name, search_name);

        if (cmp == 0) {
            found_index = mid;
            break;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (found_index != -1) {
        SET_COLOR(COLOR_BRIGHT_GREEN);
        printf("\n  Product found!\n");
        RESET_COLOR();
        display_product(&products[found_index]);
    } else {
        SET_COLOR(COLOR_RED);
        printf("\n  Product '%s' not found!\n", search_name);
        RESET_COLOR();
    }

    wait_for_enter();
}

// Low stock report
void generate_low_stock_report() {
    CLEAR_SCREEN();
    print_header("LOW STOCK REPORT");

    int found = 0;

    for (int i = 0; i < product_count; i++) {
        if (products[i].quantity <= products[i].reorder_level) {
            if (found == 0) {
                SET_COLOR(COLOR_BRIGHT_RED);
                printf("\n  Products below or at reorder level:\n");
                print_separator();
                RESET_COLOR();
            }
            display_product(&products[i]);
            printf("\n");
            found++;
        }
    }

    if (found == 0) {
        SET_COLOR(COLOR_BRIGHT_GREEN);
        printf("\n  All products are above reorder level.\n");
        RESET_COLOR();
    } else {
        SET_COLOR(COLOR_BRIGHT_RED);
        printf("\n  %d product(s) need restocking!\n", found);
        RESET_COLOR();
    }

    wait_for_enter();
}

// Category report
void generate_category_report() {
    CLEAR_SCREEN();
    print_header("CATEGORY REPORT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    // Create temporary array of categories
    char categories[MAX_PRODUCTS][MAX_CATEGORY_LEN];
    int cat_counts[MAX_PRODUCTS] = {0};
    int unique_cats = 0;

    for (int i = 0; i < product_count; i++) {
        int found = 0;
        for (int j = 0; j < unique_cats; j++) {
            if (strcmp(categories[j], products[i].category) == 0) {
                cat_counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(categories[unique_cats], products[i].category);
            cat_counts[unique_cats] = 1;
            unique_cats++;
        }
    }

    SET_COLOR(COLOR_WHITE);
    printf("\n  Category Distribution\n");
    print_separator();
    RESET_COLOR();

    for (int i = 0; i < unique_cats; i++) {
        SET_COLOR(COLOR_CYAN);
        printf("  %-20s : %d products\n", categories[i], cat_counts[i]);
        RESET_COLOR();
    }

    wait_for_enter();
}

// Supplier report
void generate_supplier_report() {
    CLEAR_SCREEN();
    print_header("SUPPLIER REPORT");

    if (product_count == 0) {
        SET_COLOR(COLOR_YELLOW);
        printf("\n  No products available.\n");
        RESET_COLOR();
        wait_for_enter();
        return;
    }

    // Create temporary array of suppliers
    char suppliers[MAX_PRODUCTS][MAX_SUPPLIER_LEN];
    int supp_counts[MAX_PRODUCTS] = {0};
    double supp_values[MAX_PRODUCTS] = {0};
    int unique_supp = 0;

    for (int i = 0; i < product_count; i++) {
        int found = 0;
        for (int j = 0; j < unique_supp; j++) {
            if (strcmp(suppliers[j], products[i].supplier) == 0) {
                supp_counts[j]++;
                supp_values[j] += products[i].price * products[i].quantity;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(suppliers[unique_supp], products[i].supplier);
            supp_counts[unique_supp] = 1;
            supp_values[unique_supp] = products[i].price * products[i].quantity;
            unique_supp++;
        }
    }

    SET_COLOR(COLOR_WHITE);
    printf("\n  Supplier Summary\n");
    print_separator();
    RESET_COLOR();

    for (int i = 0; i < unique_supp; i++) {
        SET_COLOR(COLOR_MAGENTA);
        printf("  %-25s : %d products | Total Value: $%.2f\n",
               suppliers[i], supp_counts[i], supp_values[i]);
        RESET_COLOR();
    }

    wait_for_enter();
}
