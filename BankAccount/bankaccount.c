#include "bank_account_builder.h"
#include <stdio.h>

int main() {
    // Create a `FlatBufferBuilder`, which will be used to create our
    // bank accounts' FlatBuffers.
    flatcc_builder_t builder;
    void  *buf;
    size_t size;
    
    flatcc_builder_init(&builder);
    
    test_assert(0 == Savings_create(&builder, 0));
    
    buf = flatcc_builder_finalize_aligned_buffer(&builder, &size);
    
    return 0;
}
