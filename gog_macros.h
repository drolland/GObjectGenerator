#pragma once 

#define GOG_ERROR(error,...)                \
    if ( error ){                           \
        g_error(__VA_ARGS__);         \
        goto cleanup;                       \
    }                                                                     

