#include "bankAccountDefinition_builder.h"
#include "bankAccountDefinition_reader.h"
#include <stdio.h>
#include "flatcc/support/hexdump.h"

#define test_assert(x) do { if (!(x)) { assert(0); return -1; }} while(0)

int accessBuffer(const void *buffer) {
    //Access the buffer
    
    AccountInformation_table_t accountInformation = AccountInformation_as_root(buffer);

    //Make sure it is accessible
    test_assert(accountInformation != 0);

    //TODO: Access all accounts and their information
    
    printf("Accessed flat buffer!\n");
    
    return 0;
}

// TODO: Try Obj-c & Swift example
int main() {
    flatcc_builder_t builder;
    void* buffer;
    size_t size;
    
    //Step 1. Create flatcc builder object used to generate flat buffer
    flatcc_builder_init(&builder);
    
    //Savings account information
    short savingsID = 1518;
    float savingsBalance = 252.0;
    double savingsInterestRate = .00001;
    int savingsStatus = 0;
    
    //Checking account information
    short checkingID = 1518;
    float checkingBalance = 252.0;
    double checkingInterestRate = .00001;
    int checkingStatus = 0;
    
    //TODO: If this doesn't work in the access method, might need multiple builders (it will probably work)
    
    //AccountDetails info
    flatbuffers_string_ref_t ownerName = flatbuffers_string_create_str(&builder, "John Smith"); //char[]'s are not supported, you must use the flatbuffers string
    //This is our boolean for platinum rewards
    int platinumRewards = 1;
    //Create an array of accounts
    Account_vec_start(&builder);
    //Create accounts using account information above
    Account_ref_t savings = Account_create(&builder, savingsID, savingsBalance, savingsInterestRate, savingsStatus);
    Account_ref_t checking = Account_create(&builder, checkingID, checkingBalance, checkingInterestRate, checkingStatus);
    //Add the accounts to the array
    Account_vec_push(&builder, savings);
    Account_vec_push(&builder, checking);
    //Signal the end of the array
    Account_vec_ref_t accounts = Account_vec_end(&builder);
    
    //Step 2. Create custom object using generate API call and store in builder
    //TODO: Delete old code comments like this one
    AccountInformation_create_as_root(&builder, ownerName, platinumRewards, accounts);

    //Step 3. Fill the flat buffer using builder
    buffer = flatcc_builder_finalize_aligned_buffer(&builder, &size);

    //DEBUG - Access flat buffer data and print it
    accessBuffer(buffer);

    //Step 3. Align the flat buffer
    flatcc_builder_aligned_free(buffer);

    //DEBUG - Dump the buffer to hex
    hexdump("BankAccountInformation hex", buffer, size, stdout);
    
    //Step 4. Finalize the flat buffer
    buffer = flatcc_builder_finalize_buffer(&builder, &size);
    
    //Modify the buffer...
    //This is not safe and not really possible: https://github.com/dvidelabs/flatcc/issues/165

    //Step 5. Free buffer and clear builder
    flatcc_builder_free(buffer);
    flatcc_builder_clear(&builder);

    return 0;
}
