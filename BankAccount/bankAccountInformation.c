#include "bankAccountDefinition_builder.h"
#include "bankAccountDefinition_reader.h"
#include <stdio.h>
#include "flatcc/support/hexdump.h"

#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)

int accessBuffer(const void *buffer) {
    //TODO: Uncomment this
//    //Access the buffer
//    //Savings_table_t savingsAccount = Savings_as_root(buffer);
//    Account_mutable_table_t = savingsAccount = Account_as_root(buffer);
//
//    //Make sure it is accessible
//    test_assert(savingsAccount != 0);
//
//    int16_t bankAccountNumber = Savings_accountID(savingsAccount);
//    //double interestEarned = Savings_interestEarned(savingsAccount);
//
//    //TODO: Access all savings account properties
//    printf("Bank account number is: %u\n", bankAccountNumber);
    
    return 0;
}

// TODO: Try obj-c example and then swift as well
int main() {
    flatcc_builder_t builder;
    void* buffer;
    size_t size;
    
    //Step 1. Create flatcc builder object used to generate flat buffer
    flatcc_builder_init(&builder);
    
    short savingsID = 1518;
    float savingsBalance = 252.0;
    double savingsInterestRate = .00001;
    int savingsStatus = 0;
    
    Account_table_t savingsAccount = Account_create(&builder, savingsID, savingsBalance, savingsInterestRate, savingsStatus);
    
    short checkingID = 1518;
    float checkingBalance = 252.0;
    double checkingInterestRate = .00001;
    int checkingStatus = 0;
    
    //might need multiple builders...?
    Account_table_t checkingAccount = Account_create(&builder, checkingID, checkingBalance, checkingInterestRate, checkingStatus);
    
    char owner[] = "John Smith";
    int platinumRewards = 1;
    Account_table_t accounts[] = {savingsAccount, checkingAccount};
    
    
    //Step 2. Create custom object using generate API call and store in builder
    //TODO: Delete old code comments
    //Savings_create_as_root(&builder, bankAccountNumber, accountBalance, interestRate, interestRate);
    AccountInformation_table_t accountInformation = AccountInformation_create_as_root(&builder, owner, platinumRewards, accounts);
    
    //Step 3. Fill the flat buffer using builder
    buffer = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    
    //DEBUG - Access flat buffer and savings data
    //accessBuffer(buffer);
    
    //Step 3. Align the flat buffer
    flatcc_builder_aligned_free(buffer);
    
    //DEBUG - Dump the buffer to hex
    hexdump("BankAccountInformation hex", buffer, size, stdout);
    
    //Step 4. Finalize the flat buffer
    buffer = flatcc_builder_finalize_buffer(&builder, &size);
    
    //Modify the buffer...
    //This is not safe or 100% possible: https://github.com/dvidelabs/flatcc/issues/165
    
    //Step 5. Free buffer and clear builder
    //flatcc_builder_reset(&builder);
    flatcc_builder_free(buffer);
    flatcc_builder_clear(&builder);
    
    return 0;
}
