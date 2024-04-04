
 /* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 * Version       1.0.0                                            *
 ~ Date          06.12.22                                         ~
 ~ Description   DHCP implementation with Trie                    ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include "include/dhcp.h"
#include "include/trie.h"

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <limits.h> /* CHAR_BIT */
#include <math.h> /* pow */

#define BITS_IN_BYTE CHAR_BIT
#define BITS_IN_IP (BITS_IN_BYTE * BYTES_IN_IP)

struct dhcp
{
    struct trie_node *root;
    unsigned char network_address[BYTES_IN_IP];
    size_t num_bits_in_subnet;
};


/* API Functions */
dhcp_t *DHCPCreate(const unsigned char network_address[BYTES_IN_IP], 
                   size_t num_bits_in_subnet)
{
    dhcp_t *dhcp = NULL;
    unsigned char server_address[BYTES_IN_IP] = {255,255,255,254};
    unsigned char broadcast_address[BYTES_IN_IP] = {255,255,255,255};
    unsigned char result[BYTES_IN_IP] = {0};

    assert(network_address);
    assert(num_bits_in_subnet <= (BITS_IN_IP - 2));

    dhcp = (dhcp_t *)calloc(sizeof(dhcp_t), 1);
    if (NULL == dhcp)
    {
        return NULL;
    }

    dhcp->root = TrieCreate(num_bits_in_subnet);
    if (NULL == dhcp->root)
    {
        free(dhcp); dhcp = NULL;
        return NULL;
    }

    dhcp->num_bits_in_subnet = num_bits_in_subnet;
    memcpy(dhcp->network_address, network_address, BYTES_IN_IP);

    /* allocate network address */
    if (FAILURE == DHCPAllocateIP(dhcp, 
                                  dhcp->network_address, 
                                  result))
    {
        TrieDestroy(dhcp->root); dhcp->root = NULL;
        free(dhcp); dhcp = NULL;
        return NULL;
    }

    /* allocate server address */
    if (FAILURE == DHCPAllocateIP(dhcp, 
                                  server_address, 
                                  result))
    {
        TrieDestroy(dhcp->root); dhcp->root = NULL;
        free(dhcp); dhcp = NULL;
        return NULL;
    }

    /* allocate broadcast address */
    if (FAILURE == DHCPAllocateIP(dhcp, 
                                  broadcast_address, 
                                  result))
    {
        TrieDestroy(dhcp->root); dhcp->root = NULL;
        free(dhcp); dhcp = NULL;
        return NULL;
    }

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{   
    TrieDestroy(dhcp->root); dhcp->root = NULL;
    free(dhcp); dhcp = NULL;
}

status_t DHCPAllocateIP(dhcp_t *dhcp, 
                        const unsigned char requested_ip[BYTES_IN_IP], 
                        unsigned char result_ip[BYTES_IN_IP])
{
    status_t status = 0;
    size_t i = 0;
    unsigned char requested_cpy[BYTES_IN_IP] = {0};
    unsigned char all_zeros[BYTES_IN_IP] = {0};

    memcpy(result_ip, all_zeros, BYTES_IN_IP);
    memcpy(requested_cpy, requested_ip, BYTES_IN_IP);

    status = TrieInsert(dhcp->root, requested_cpy, result_ip);
    
    for (i = 0; i < BYTES_IN_IP; ++i)
    {
        result_ip[i] |= dhcp->network_address[i];
    }

    return status;
}

status_t DHCPFreeIP(dhcp_t *dhcp, const unsigned char ip_to_free[BYTES_IN_IP])
{
    return TrieRemove(dhcp->root, ip_to_free);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    size_t total_capacity = 0;

    assert(dhcp);
    
    total_capacity = pow(2, (BITS_IN_IP - dhcp->num_bits_in_subnet));
    

    return (total_capacity - TrieSize(dhcp->root));
}

