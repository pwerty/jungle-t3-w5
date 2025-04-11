#include <stdio.h>

struct Person {
    char name[20];
    int age;
    char address[100];
};



int main()
{
    struct Person personList[3];
    // name에는 "홍길동", age에는 30, address에는 "서울시 용산구 한남동"
    struct Person p1 = { .name = "홍길동", .age = 30, .address = "서울시 용산구 한남동" };

    printf("이름: %s\n", p1.name);       // 이름: 홍길동
    printf("나이: %d\n", p1.age);        // 나이: 30
    printf("주소: %s\n", p1.address);    // 주소: 서울시 용산구 한남동

    // name에는 "고길동", age에는 40, address에는 "서울시 서초구 반포동"
    struct Person p2 = { "고길동", 40, "서울시 서초구 반포동" };

    printf("이름: %s\n", p2.name);       // 이름: 고길동
    printf("나이: %d\n", p2.age);        // 나이: 40
    printf("주소: %s\n", p2.address);    // 주소: 서울시 서초구 반포동

    struct Person p3 = {"동동동", 25, "용인 처인구 영문로 5555555555555번지"};

    printf("이름: %s\n", p3.name);      
    printf("나이: %d\n", p3.age);        
    printf("주소: %s\n", p3.address);    

    personList[0] = p1;
    personList[1] = p2;
    personList[2] = p3;
    printf("\n\n\n");
    for(int i = 0; i < 3; i++)
    {
        printf("이름: %s\n", personList[i].name);
        printf("나이: %d\n", personList[i].age);        
        printf("주소: %s\n", personList[i].address);    
    }

    return 0;
}