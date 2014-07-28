/****************************************************************************
 * net/ieee80211/ieee80211_priv.h
 *
 * Copyright (c) 2008 Damien Bergamini <damien.bergamini@free.fr>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ****************************************************************************/

#ifndef __NET_IEEE80211_IEEE80211_PRIV_H
#define __NET_IEEE80211_IEEE80211_PRIV_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define SEQ_LT(a,b)    \
    ((((uint16_t)(a) - (uint16_t)(b)) & 0xfff) > 2048)

#define IEEE80211_AID_SET(b, w) \
    ((w)[IEEE80211_AID(b) / 32] |= (1 << (IEEE80211_AID(b) % 32)))
#define IEEE80211_AID_CLR(b, w) \
    ((w)[IEEE80211_AID(b) / 32] &= ~(1 << (IEEE80211_AID(b) % 32)))
#define IEEE80211_AID_ISSET(b, w) \
    ((w)[IEEE80211_AID(b) / 32] & (1 << (IEEE80211_AID(b) % 32)))

#define IEEE80211_RSNIE_MAXLEN                        \
    (2 +        /* Version */                    \
     4 +        /* Group Data Cipher Suite */            \
     2 +        /* Pairwise Cipher Suite Count */        \
     4 * 2 +    /* Pairwise Cipher Suite List (max 2) */    \
     2 +        /* AKM Suite List Count */            \
     4 * 4 +    /* AKM Suite List (max 4) */            \
     2 +        /* RSN Capabilities */                \
     2 +        /* PMKID Count */                \
     16 * 1 +   /* PMKID List (max 1) */            \
     4)                         /* 11w: Group Integrity Cipher Suite */

#define IEEE80211_WPAIE_MAXLEN                        \
    (4 +        /* MICROSOFT_OUI */                \
     2 +        /* Version */                    \
     4 +        /* Group Cipher Suite */            \
     2 +        /* Pairwise Cipher Suite Count */        \
     4 * 2 +    /* Pairwise Cipher Suite List (max 2) */    \
     2 +        /* AKM Suite List Count */            \
     4 * 2)                     /* AKM Suite List (max 2) */

struct ieee80211_rsnparams
  {
    uint16_t rsn_nakms;
    uint32_t rsn_akms;
    uint16_t rsn_nciphers;
    uint32_t rsn_ciphers;
    enum ieee80211_cipher rsn_groupcipher;
    enum ieee80211_cipher rsn_groupmgmtcipher;
    uint16_t rsn_caps;
    uint8_t rsn_npmkids;
    const uint8_t *rsn_pmkids;
  };

/* unaligned big endian access */

#define BE_READ_2(p)                \
    ((uint16_t)                \
         ((((const uint8_t *)(p))[0] << 8) |    \
          (((const uint8_t *)(p))[1])))

#define BE_READ_8(p)                        \
    ((uint64_t)(p)[0] << 56 | (uint64_t)(p)[1] << 48 |    \
     (uint64_t)(p)[2] << 40 | (uint64_t)(p)[3] << 32 |    \
     (uint64_t)(p)[4] << 24 | (uint64_t)(p)[5] << 16 |    \
     (uint64_t)(p)[6] <<  8 | (uint64_t)(p)[7])

#define BE_WRITE_2(p, v) do {            \
    ((uint8_t *)(p))[0] = (v) >> 8;    \
    ((uint8_t *)(p))[1] = (v) & 0xff;    \
} while (0)

#define BE_WRITE_8(p, v) do {            \
    (p)[0] = (v) >> 56; (p)[1] = (v) >> 48;    \
    (p)[2] = (v) >> 40; (p)[3] = (v) >> 32;    \
    (p)[4] = (v) >> 24; (p)[5] = (v) >> 16;    \
    (p)[6] = (v) >>  8; (p)[7] = (v);    \
} while (0)

/* unaligned little endian access */
#define LE_READ_2(p)                    \
    ((uint16_t)                    \
     ((((const uint8_t *)(p))[0]) |        \
      (((const uint8_t *)(p))[1] <<  8)))

#define LE_READ_4(p)                    \
    ((uint32_t)                    \
     ((((const uint8_t *)(p))[0])       |        \
      (((const uint8_t *)(p))[1] <<  8) |        \
      (((const uint8_t *)(p))[2] << 16) |        \
      (((const uint8_t *)(p))[3] << 24)))

#define LE_READ_6(p)                        \
    ((uint64_t)(p)[5] << 40 | (uint64_t)(p)[4] << 32 |    \
     (uint64_t)(p)[3] << 24 | (uint64_t)(p)[2] << 16 |    \
     (uint64_t)(p)[1] <<  8 | (uint64_t)(p)[0])

#define LE_WRITE_2(p, v) do {            \
    ((uint8_t *)(p))[0] = (v) & 0xff;    \
    ((uint8_t *)(p))[1] = (v) >> 8;    \
} while (0)

#define LE_WRITE_4(p, v) do {            \
    (p)[3] = (v) >> 24; (p)[2] = (v) >> 16;    \
    (p)[1] = (v) >>  8; (p)[0] = (v);    \
} while (0)

#define LE_WRITE_6(p, v) do {            \
    (p)[5] = (v) >> 40; (p)[4] = (v) >> 32;    \
    (p)[3] = (v) >> 24; (p)[2] = (v) >> 16;    \
    (p)[1] = (v) >>  8; (p)[0] = (v);    \
} while (0)

#endif /* __NET_IEEE80211_IEEE80211_PRIV_H */
