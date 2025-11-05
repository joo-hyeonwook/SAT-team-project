#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// ======= 캐릭터 기본 클래스 =======
class Character {
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
    Character(string name, int hp, int atk)
        : name(name), hp(hp), atk(atk) {  // 생성자에게 기본값 배부
    }

    virtual void TakeDamage(int damage) {
        hp = hp - damage;
        if (hp < 0) hp = 0;  // 현실적으로 hp가 0이하인건 말이 안됨 -> 0이하로 떨어지면 0으로 고정
    }

    virtual void Attack(Character* target) {
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

        target->TakeDamage(damage);
        cout << name << "의 공격! " << endl << result << " --> (피해: " << damage << ")" << endl;
        cout << target->name << "의 남은 HP: " << target->hp << endl;
    }


    virtual double Defend() {
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
    int GetATK() { return atk; }
};


// ======= 플레이어 클래스 =======
class Player : public Character {
private:
    bool isDefending;
    int itemCount;

public:
    Player(string name, int hp, int atk)
        : Character(name, hp, atk), isDefending(false), itemCount(0) {
    }
    
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

    void ShowInfo() {
        cout << "< Information >" << endl;
        cout << ">name : " << name << endl;
        cout << ">HP : " << hp << endl;
        cout << ">HP_item : " << itemCount << endl;
    }

    bool IsAlive() { return hp > 0; }
};



// ======= 적 클래스 =======
class Enemy : public Character {
public:
    Enemy(string name, int hp, int atk)
        : Character(name, hp, atk) {
    }

    void Attack(Character* target) override {
        cout << name << "의 차례!" << endl;
        int roll = RollDice(); // 교체  RollDice();    rand() % 12 + 1;
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
        system("cls");
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
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    return;
                }
                else {
                    cout << "\n도망 실패! 적의 반격!\n";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                }
            }
            else {
                cout << "잘못된 입력입니다!\n";
                continue;
            }

            if (enemy.GetHP() <= 0) break;

            enemy.Attack(&player);
            this_thread::sleep_for(chrono::milliseconds(1000));
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
    srand((unsigned int)time(nullptr));
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
