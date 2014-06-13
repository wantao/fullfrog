#include <stdio.h>
#include <stdlib.h>


struct epollop* g_epollop = NULL;

int main()
{
    struct event_base *base;
    struct event_config *config;

    config = event_config_new();
    event_config_set_flag(config, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST);
    base = event_base_new_with_config(config);
    if (!base) {
        printf(stderr, "Could not initialize libevent with EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST!\n");
        return -1;
    }

    g_epollop = epoll_init(base);
    if (NULL == g_epollop){
        printf("epoll_init failure");
        return -1;
    }




    return 0;
}