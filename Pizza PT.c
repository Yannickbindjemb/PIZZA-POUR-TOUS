#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
int main() {
    char *meals[6] = {
        "1 small Pizza + 1 small shawarma + 1 pepsi",
        "1 medium Pizza + 10 wings + fries + 1 pepsi",
        "1 medium Pizza + 1 medium shawarma + 1 pepsi",
        "1 large Pizza + 1 medium shawarma + 1 pepsi",
        "1 X-Large Pizza + 1 large shawarma + 1 pepsi",
        "1 X-Large Pizza + 15 wings + 1 pepsi"
    };
    double price[6] = {20.49, 21.99, 24.49, 25.99, 28.49, 29.99};

    int choice, invoice = 1, totalSold = 0, i;
    double totalSales = 0;
    char phone[30], address[100];
    time_t t;
    struct tm*tm_info;
    char buffer[80];

    printf("=== Pizza Pour Tous (PPT) ===\n");

    do {
        printf("\n1. Bill an order\n2. Display totals\n3. Quit\nChoice: ");
        scanf("%d", &choice);
        getchar(); // clean Enter

        if (choice == 1) {
            printf("\n--- Invoice %d ---\nPhone: ", invoice);
            fgets(phone, 30, stdin);
            printf("Address: ");
            fgets(address, 100, stdin);

            double subtotal = 0;
            char addMore;

            do {
                int num, qty;
                char pizza, pay;

                printf("\n--- MEALS ---\n");
                for (i = 0; i < 6; i++)
                    printf("%d. %s - $%.2f\n", i + 1, meals[i], price[i]);

                printf("Meal number (1-6): ");
                scanf("%d", &num);
                getchar();

                printf("Pizza type (v,f,t,e,m): ");
                scanf(" %c", &pizza);
                getchar();

                printf("Quantity: ");
                scanf("%d", &qty);
                getchar();

                printf("Payment (C=Cash, D=Debit, R=Credit): ");
                scanf(" %c", &pay);
                getchar();

                subtotal += price[num - 1] * qty;
                totalSold += qty;

                printf("Add another? (o/n): ");
                scanf(" %c", &addMore);
                getchar();

                // save last payment for invoice
                phone[0] = phone[0]; // keep phone
                address[0] = address[0];
                // print payment below using pay
                // store it in choice 
                //  print invoice at end with last pay
                if (addMore != 'o') {
                    double gst = subtotal * 0.05;
                    double qst = subtotal * 0.0975;
                    double total = subtotal + gst + qst;

                    printf("\n===== PIZZA POUR TOUS =====\n");
                    printf("Invoice: %d\nPhone: %sAddress: %s", invoice, phone, address);
                    printf("Payment: %c\n", toupper(pay));
                    printf("-----------------------------\n");
                    printf("Subtotal: $%.2f\n", subtotal);
                    printf("GST (5%%): $%.2f\n", gst);
                    printf("QST (9.975%%): $%.2f\n", qst);
                    printf("TOTAL: $%.2f\n", total);
                    printf("=============================\n");

                    totalSales += total;
                    invoice++;
                }
            } while (addMore == 'o');

        } else if (choice == 2) {
            printf("\n===== TOTALS =====\n");
            t=time(NULL);
            tm_info=localtime(&t);
            strftime(buffer, sizeof(buffer),"%d/%m/%Y %H:%M:%S",buffer);
            printf("Total meals sold: %d\n", totalSold);
            printf("Total sales: $%.2f\n", totalSales);
        }
    } while (choice != 3);

    printf("Thanks see you next time\n");
    return 0;
}

