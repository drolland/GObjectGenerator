#pragma once 

#define GOG_ERROR(error,...)                \
    if ( error ){                           \
        g_error(__VA_ARGS__);               \
        g_clear_error(&error);               \
        goto cleanup;                       \
    }                                                                     

