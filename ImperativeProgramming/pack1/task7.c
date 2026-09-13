#include <stdio.h>
#include <math.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int apartmentFromCall = -1;
    scanf("%d", &apartmentFromCall);
    if (apartmentFromCall <= 0) return 0;
    
    int oldCallApartment = -1, oldCallEntrance = -1, oldCallFloor = -1, totalFloors = -1;
    scanf("%d %d %d %d", &oldCallApartment, &oldCallEntrance, &oldCallFloor, &totalFloors);
    if (oldCallApartment <= 0 || oldCallEntrance <= 0 || oldCallFloor <= 0 || totalFloors <= 0) return 0;

    int areasBefore = (oldCallEntrance - 1) * totalFloors + oldCallFloor - 1;
    int apartmentsOnArea = ceil((double)oldCallApartment / ((double)areasBefore + 1.0));

    int apartmentsOnEntrance = totalFloors * apartmentsOnArea;
    int callApartmentEntrance = (apartmentFromCall - 1) / apartmentsOnEntrance + 1;
    int callApartmentFloor = (apartmentFromCall - 1) % apartmentsOnEntrance / apartmentsOnArea + 1;

    printf("%d %d", callApartmentEntrance, callApartmentFloor);

    return 0;
}