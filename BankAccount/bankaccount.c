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
    //Create flatcc builder object used to generate flat buffer
    flatcc_builder_t builder;
    void* buffer;
    size_t size;
    flatcc_builder_init(&builder);
    
    //TODO: change to account number
//    short bankAccountNumber = 1518;
//    double accountBalance = 252.0;
//    double interestEarned = 2.00;
//    float interestRate = .001;
    
    int16_t bankAccountNumber = 1518;
    int64_t accountBalance = 252.0;
    double interestEarned = 2.00;
    double interestRate = .001;
    
    //Step 1. Set our builder - Call the method generated in our fbs file
    Savings_ref_t savingsAccount = Savings_create_as_root(&builder, bankAccountNumber, accountBalance, interestRate, interestRate);
    
    //Savings_ref_t savingsAccount = Savings_create_as_root(&builder, bankAccountNumber, accountBalance, interestRate, interestRate);
    
    //TODO: ...?
    // ns(Monster_ref_t) orc = ns(Monster_create(B, ...));
    // flatcc_builder_buffer_create(orc);
    
    //Step 2. Fill the buffer
    buffer = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    
    //DEBUG - Access buffer
    accessBuffer(buffer);
    
    //Step 3. Align the buffer
    flatcc_builder_aligned_free(buffer);
    
    //DEBUG - Dump the buffer
    hexdump("Bank account hex", buffer, size, stdout);
    
    //Step 4. Finalize the buffer
    buffer = flatcc_builder_finalize_buffer(&builder, &size);
    
    //Step 5. Cleanup
    
    //Modify the buffer...?
    //You do not modify, you clear the buffer and create a new buffer.
    
    //TODO: Move this?
    //The builder can be reset which is faster than creating a new one
    //flatcc_builder_reset(&builder);
    
    //buf = flatcc_builder_finalize_buffer(&builder, &size);
    //flatcc_builder_clear(&builder);
    
    return 0;
}
