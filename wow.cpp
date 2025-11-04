#include <iostream>
#include <string>
#include <cstdlib> // 난수 생성하는 헤더파일 rand() 와 srand()를 사용하기 위해서
#include <ctime> // time(NULL) 같은 함수를 제공해서 srand(time(nullptr))를 사용하기 위해서 필요함 
#include <thread> // 전투중에 잠깐 프로그램을 일시정지하여 텀을 만들어서 읽기 편하게 해주는 함수를 제공하는 파일
#include <chrono> // 시간 단위를 표현하기 위해서 사용

using namespace std;

// ======= 캐릭터 기본 클래스 =======
class Character { // player & enemy 모두에 해당되는 공통적 특징을 하나로 만든 class
protected:   // 클래스 자신과 자식 클래스도 접근 가능
    string name;
    int hp;
    int atk;

    int RollDice() {
        int dice1 = rand() % 6 + 1;  // 1 ~ 6 사이 중 하나 난수 생성.
        int dice2 = rand() % 6 + 1;  
        return dice1 + dice2;
    }

public:
    Character(string name, int hp, int atk) // player와 enemy 모두가 공통적으로 같는 정보 그리고 생성자
        : name(name), hp(hp), atk(atk) {  // 객체를 초기화
    }

    virtual void TakeDamage(int damage) {
        hp = hp - damage;
        if (hp < 0) hp = 0;  // hp가 공격을 통해 음수가 되는경우 그냥 hp = 0으로 고정 Ex) hp가 10 남았는데 공격이 20이 가해지는 경우
    }

    virtual void Attack(Character* target) { // player와 enemy 모두가 공통적으로 적용되는 공격함수
        int roll = RollDice();
        int damage = 0;
        string result;
        if (roll <= 6) {
            result = " --> 공격 실패! --> 애송이 더 훈련하고 와ㄹr..";
            damage = 0;
        }
        else if (roll >6 && roll <= 9) {
            result = " --> 공격 성공! --> 후.. 상남자의 불주먹이ㄷr..";
            damage = atk;
        }
        else {
            result = " --> 대성공! --> 넌 해병대가 어울린ㄷr.. ";
            damage = atk * 2;
        }
        // 남은 hp 보여주는 코드
        target->TakeDamage(damage);
        cout << name << "의 공격! " << endl << result << " --> (피해: " << damage << ")" << endl;
        cout << target->name << "의 남은 HP: " << target->hp << endl;
    }
    

    virtual double Defend() { // double을 반환하는 이유: 소수점을 반환하기 위해서
        int roll = RollDice();
        double reduction;
        string result;

        if (roll <= 6) {
            reduction = 1.0;
            result = "방어 실패! --> 아..아이고 아파라..";
        }
        else if (roll >6 && roll <= 9) {
            reduction = 0.5;
            result = "방어 성공! --> 휴~ 피해 절반!";
        }
        else {
            reduction = 0.0;
            result = "대성공! --> 휴우우~~ 피해 완전 방어!";
        }

        cout << name << "의 " << result << endl;
        return reduction;
    }
    
    string GetName() { return name; }  
    int GetHP() { return hp; }
    int GetATK() { return atk; }  // Getter의 함수는 값을 안전하게 꺼내기 위해서 사용하는 함수
};


// ======= 플레이어 클래스 =======
class Player : public Character { //player가 character에 상속됨 즉, player는 character의 모든 기능과 멤버를 물려받음 + 자기 자신의 정보 포함도 가능
private:
    // player에서만의 추가 멤버들
    bool isDefending; 
    int itemCount;

public:
    Player(string name, int hp, int atk)
        : Character(name, hp, atk), isDefending(false), itemCount(0) { //부모 클래스의 생성자를 호출해서 palyer의 name,hp,atk 설정
    }
    // 체력회복은 player에만 해당되므로 내용 추가한거
    void GetItem() {
        itemCount++;
        cout << ">체력회복 물약을 획득했습니다." << endl;
        cout << ">현재 아이템 개수: " << itemCount << endl;
    }

    void UseItem() {
        if (itemCount <= 0) {
            cout << ">아이템이 없습니다!" << endl;
            return;
        }

        hp += 10;
        itemCount--;
        cout << ">체력회복 물약을 사용했습니다!" << endl;
        cout << ">현재 HP : " << GetHP() << endl;
        cout << ">남은 물약 개수 : " << itemCount << endl;
    }

    double Defend() override {
        isDefending = true;
        return Character::Defend();
    }

    bool TryEscape() {
        int roll = RollDice();
        if (roll <= 6) {
            cout << " --> 도망 가지 못했어! --> 나..납치 당했다.." << endl;
            return false;
        }
        else if (roll <= 9) {
            cout << " --> 도망 성공! --> 드디어 노예 탈출이야.. ㅠㅠ" << endl;
            return true;
        }
        else {
            cout << " --> 대성공! --> 후.. 도비는 자유예요" << endl;
            return true;
        }
    }

    void ShowInfo() { // player의 바뀐 정보를 출력하는 함수
        cout << "< Information >" << endl;
        cout << ">name : " << name << endl;
        cout << ">HP : " << hp << endl;
        cout << ">HP_item : " << itemCount << endl;
    }

    bool IsAlive() { return hp > 0; }
};



// ======= 적 클래스 =======
class Enemy : public Character { // enemy도 character에 상속받음
public:
    Enemy(string name, int hp, int atk)
        : Character(name, hp, atk) {  // enemy가 부모 클래스 호출해서 name, hp, atk 설정
    }

    void Attack(Character* target) override {
        cout << name << "의 차례!" << endl;
        int roll = RollDice(); // character에서 가지고 오기
        int damage;

        if (roll <= 6) {
            cout << name << "의 공격이 빗나갔습니다!" << endl;
            return;
        }
        else if (roll > 6 &&roll <= 9) {
            damage = atk;
            cout << name << "의 공격 성공! --> 피해 " << damage << endl;
        }
        else {
            damage = atk * 2;
            cout << name << "의 대성공 공격! 피해 " << damage << endl;
        }

        target->TakeDamage(damage);
        cout << target->GetName() << "의 남은 HP: " << target->GetHP() << endl;
    }
};




// ======= 전투 담당 클래스 =======
class Combat {
public:
    void StartCombat(Player& player, Enemy& enemy) {
        system("cls"); //콘솔 화면을 지우는 명령어
        cout << "전투 시작!" << endl;
        cout << player.GetName() << " (HP: " << player.GetHP() << ")  VS  "
            << enemy.GetName() << " (HP: " << enemy.GetHP() << ")" << endl;

        while (player.GetHP() > 0 && enemy.GetHP() > 0) {
            cout << "행동을 선택하세요:" << endl;
            cout << "1. 공격" << endl;
            cout << "2. 방어" << endl;
            cout << "3. 아이템 사용" << endl;
            cout << "4. 도망" << endl;
            cout << "> ";
            string choice;
            getline(cin, choice);

            if (choice == "1") {
                player.Attack(&enemy);
            }
            else if (choice == "2") {
                player.Defend();
            }
            else if (choice == "3") {
                player.UseItem();
            }
            else if (choice == "4") {
                if (player.TryEscape()) {
                    cout << "\n성공적으로 도망쳤습니다!\n";
                    this_thread::sleep_for(chrono::milliseconds(1000)); // 출력을 1초 늦게 해줘서 읽기 편하게 해주는 코드
                    return;
                }
                else {
                    cout << "\n도망 실패! 적의 반격!\n";
                    this_thread::sleep_for(chrono::milliseconds(1000)); // 출력을 1초 늦게 해줘서 읽기 편하게 해주는 코드
                }
            }
            else {
                cout << "잘못된 입력입니다!\n";
                continue;
            }

            if (enemy.GetHP() <= 0) break;

            enemy.Attack(&player);
            this_thread::sleep_for(chrono::milliseconds(1000)); // 출력을 1초 늦게 해줘서 읽기 편하게 해주는 코드
            cout << endl;
        }

        EndCombat(player, enemy);
    }

private:
    void EndCombat(Player& player, Enemy& enemy) {
        cout << endl;
        if (player.GetHP() <= 0)
            cout << player.GetName() << "이(가) 쓰러졌습니다... 게임 오버!\n";
        else
            cout << enemy.GetName() << "을(를) 쓰러뜨렸습니다!\n";
    }
};




// ======= 메인 함수 =======
int main() {
    srand((unsigned int)time(nullptr)); //난수의 시드를 현재로 설정해야지 rand()함수가 매번 다른 숫자를 만듦 아니면 고정된 값이 들어가게 됨
    string n;
    cout << "키미노 나마에와..?  ";
    getline(cin, n);
    Player player(n, 50, 10);
    Enemy enemy("슬라임", 30, 5);
    Combat combat;

    player.GetItem();
    combat.StartCombat(player, enemy);

    
    // 준호는 아무것도 안한 것 같지만 다 오해입니다 비록 시험 때문에 다른 팀원들에 비해 참여가 부족하긴 했지만 위의 코드를 돌아갈 수 있게 마무리 작업을 완벽하게 수행 wow
    return 0;
}
