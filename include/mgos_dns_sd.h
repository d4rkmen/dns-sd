/*
 * Copyright (c) 2014-2018 Cesanta Software Limited
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>

#include "common/mg_str.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Return currently configure DNS-SD hostname.
 */
const char *mgos_dns_sd_get_host_name(void);

/* TXT record key/value entry */
struct mgos_dns_sd_txt_entry {
  const char *key;
  struct mg_str value;
};

/*
 * Add a service instance.
 * If service instance already exists, its definition will be replaced.
 * A record will be added automatically to point to the device.
 * If txt_entries is not NULL, it must end with an entry with key=NULL.
 *
 * Example (for Apple HAP):
 *
 * const struct mgos_dns_sd_txt_entry gizmo_txt[] = {
 *     {.key = "c#", .value = MG_MK_STR("1")},
 *     {.key = "ff", .value = MG_MK_STR("0")},
 *     {.key = "pv", .value = MG_MK_STR("1.0")},
 *     {.key = "id", .value = MG_MK_STR("11:22:33:44:55:66")},
 *     {.key = "md", .value = MG_MK_STR("Fancy Gizmo 9000")},
 *     {.key = "s#", .value = MG_MK_STR("1")},
 *     {.key = "sf", .value = MG_MK_STR("1")},
 *     {.key = "ci", .value = MG_MK_STR("8")},  // Switch
 *     {.key = NULL},
 * };
 * mgos_dns_sd_add_service_instance("gizmo9000", "_hap._tcp", 8080, gizmo_txt);
 */
bool mgos_dns_sd_add_service_instance(
    const char *name, const char *proto, int port,
    const struct mgos_dns_sd_txt_entry *txt_entries);

/* Stop advertising the specified instance. */
bool mgos_dns_sd_remove_service_instance(const char *instance,
                                         const char *proto, int port);

/* Send a DNS-SD advertisement message now. */
void mgos_dns_sd_advertise(void);

/* Send a goodbye packet */
void mgos_dns_sd_goodbye(void);

/* Set host name. If NULL is passed, updates from config. */
bool mgos_dns_sd_set_host_name(const char *name);

#ifdef __cplusplus
}
#endif
