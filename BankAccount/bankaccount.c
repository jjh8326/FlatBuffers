#include "bank_account_builder.h"
#include "bank_account_reader.h"
#include <stdio.h>
#include "flatcc/support/hexdump.h"

#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)

int accessBuffer(const void *buffer) {
    //Access the buffer
    Savings_table_t savingsAccount = Savings_as_root(buffer);
    //Make sure it is accessible
    test_assert(savingsAccount != 0);
    
    printf("BUFFER NOT EMPTY\n");
    
    int16_t bankAccountNumber = Savings_accountID(savingsAccount);
    //double interestEarned = Savings_interestEarned(savingsAccount);
    
    printf("Bank account number is: %u\n", bankAccountNumber);
    
    return 0;
}

int main() {
    flatcc_builder_t builder;
    void* buffer;
    size_t size;
    
    //Step 1. Create flatcc builder object used to generate flat buffer
    flatcc_builder_init(&builder);
    
    //TODO: Add more fields to IDL file and make names the same
    short bankAccountNumber = 1518;
    double accountBalance = 252.0;
    double interestEarned = 2.00;
    float interestRate = .001;
    
    //Step 2. Create custom object using generate API call and store in builder
    Savings_create_as_root(&builder, bankAccountNumber, accountBalance, interestRate, interestRate);
    
    //Step 3. Fill the flat buffer using builder
    buffer = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    
    //DEBUG - Access flat buffer and savings data
    accessBuffer(buffer);
    
    //Step 3. Align the flat buffer
    flatcc_builder_aligned_free(buffer);
    
    //DEBUG - Dump the buffer to hex
    hexdump("Bank account hex", buffer, size, stdout);
    
    //Step 4. Finalize the flat buffer
    buffer = flatcc_builder_finalize_buffer(&builder, &size);
    
    //Modify the buffer...?
    //You do not modify, you clear the buffer and create a new buffer.
    
    //Step 5. Free buffer and clear builder
    //flatcc_builder_reset(&builder);
    flatcc_builder_free(buffer);
    flatcc_builder_clear(&builder);
    
    return 0;
}
