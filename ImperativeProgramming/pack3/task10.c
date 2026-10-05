#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
typedef __int128 i128;

const ll SCALE = 1000000000LL;


ll max(ll a, ll b) {
    return a > b ? a : b;
}


int getBitsCount(ll n) {
    int count = 0;

    while (n > 0) {
        count += n & 1LL;
        n >>= 1;
    }

    return count;
}

ll getFixedMaxNum(ll n, int needBits) {
    if (getBitsCount(n) <= needBits) {
        return n;
    }

    ll result = 0;
    int count = 0;

    for (int bit = 62; bit >= 0; --bit) {
        if ((n >> bit) & 1LL) {
            if (count < needBits) {
                result |= 1LL << bit;
                ++count;
            }
        }
    }

    return result;
}

ll getFixedMinNum(ll n, int needBits) {
    if (getBitsCount(n) <= needBits) {
        return n;
    }

    for (int bit = 0; bit < 63; ++bit) {

        if (((n >> bit) & 1LL) == 0) {

            ll upper = n >> (bit + 1);

            if (getBitsCount(upper) + 1 <= needBits) {

                ll result = upper << (bit + 1);

                result |= 1LL << bit;

                return result;
            }
        }
    }

    return 0;
}

void getParts(ll totalFly, int exists, ll *parts) {
    ll number = totalFly + 1;

    int count = 0;

    for (int bit = 0; bit < 63; ++bit) {
        if ((number >> bit) & 1LL) {
            parts[count++] = 1LL << bit;
        }
    }

    int i = 0;

    while (count < exists + 1) {

        if (parts[i] == 1) {
            ++i;
            continue;
        }

        parts[i] /= 2;

        parts[count] = parts[i];

        ++count;
    }
}

void getFlyPositions(
    i128 *result,
    int exists,
    ll len,
    ll totalFly,
    ll flyWidth
) {
    ll *parts =
        malloc((exists + 1) * sizeof(ll));

    getParts(totalFly, exists, parts);

    i128 remaining =
        (i128)(len - totalFly * flyWidth) * SCALE;

    i128 position = 0;

    for (int i = 0; i <= exists; ++i) {

        i128 gap =
            (i128)(parts[i] - 1)
            * flyWidth
            * SCALE;

        i128 capacity =
            (i128)parts[i]
            * flyWidth
            * SCALE
            - 1;

        i128 add;

        if (remaining < capacity) {
            add = remaining;
        } else {
            add = capacity;
        }

        gap += add;
        remaining -= add;

        if (i == exists) {
            break;
        }

        position += gap;

        result[i] =
            position
            + (i128)flyWidth * SCALE / 2;

        position +=
            (i128)flyWidth * SCALE;
    }

    free(parts);
}

void printPosition(i128 position) {
    ll integerPart =
        (ll)(position / SCALE);

    ll fractionalPart =
        (ll)(position % SCALE);

    printf(
        "%lld.%09lld\n",
        integerPart,
        fractionalPart
    );
}


int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int existsFly;

    ll widthFly;
    ll stickLen;

    scanf(
        "%d %lld",
        &existsFly,
        &widthFly
    );

    scanf(
        "%lld",
        &stickLen
    );


    ll heuristicMin =
        (stickLen + widthFly)
        / (2 * widthFly);

    heuristicMin =
        max(heuristicMin, existsFly);

    ll heuristicMax =
        stickLen / widthFly;

    ll minFly =
        getFixedMinNum(
            heuristicMin + 1,
            existsFly + 1
        ) - 1;

    ll maxFly =
        getFixedMaxNum(
            heuristicMax + 1,
            existsFly + 1
        ) - 1;


    printf(
        "%lld %lld\n",
        minFly,
        maxFly
    );


    i128 *positions =
        malloc(existsFly * sizeof(i128));


    getFlyPositions(
        positions,
        existsFly,
        stickLen,
        minFly,
        widthFly
    );

    for (int i = 0; i < existsFly; ++i) {
        printPosition(positions[i]);
    }

    getFlyPositions(
        positions,
        existsFly,
        stickLen,
        maxFly,
        widthFly
    );

    for (int i = 0; i < existsFly; ++i) {
        printPosition(positions[i]);
    }


    free(positions);

    return 0;
}