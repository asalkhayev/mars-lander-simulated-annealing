#include <iostream>
#include <cmath>
using namespace std;

struct MarsLander {
    static const int Y_MARGIN = 20;
    static const int SPEED_MARGIN = 5;
    static const int MAX_DY = 40;
    static const int MAX_DX = 20;
    static constexpr double GRAVITY = 3.711;

    int x, y;
    int dx, dy;
    int fuel;
    int angle, power;
    int targetL, targetR, targetY;

    void init(int X, int Y, int dX, int dY, int Fuel, int Angle, int Power) {
        x = X;
        y = Y;
        dx = dX;
        dy = dY;
        fuel = Fuel;
        angle = Angle;
        power = Power;
    }

    void setTarget(int L, int R, int Yt) {
        targetL = L;
        targetR = R;
        targetY = Yt;
    }

    bool isOverTarget() const {
        return targetL <= x && x <= targetR;
    }

    bool isFinishing() const {
        return y < targetY + Y_MARGIN;
    }

    bool hasSafeSpeed() const {
        return std::abs(dx) <= MAX_DX - SPEED_MARGIN &&
               std::abs(dy) <= MAX_DY - SPEED_MARGIN;
    }

    bool goesInWrongDirection() const {
        return (x < targetL && dx < 0) || (targetR < x && dx > 0);
    }

    bool goesTooFastHorizontally() const {
        return std::abs(dx) > 4 * MAX_DX;
    }

    bool goesTooSlowHorizontally() const {
        return std::abs(dx) < 2 * MAX_DX;
    }

    int angleToSlow() const {
        double speed = std::sqrt((double)dx * dx + (double)dy * dy);
        if (speed == 0.0) return 0;
        double ratio = (double)dx / speed;
        if (ratio > 1.0) ratio = 1.0;
        if (ratio < -1.0) ratio = -1.0;
        double a = std::asin(ratio);
        int deg = (int)std::round(a * 180.0 / M_PI);
        return deg;
    }

    int angleToAimTarget() const {
        double a = std::acos(GRAVITY / 4.0);
        int deg = (int)std::round(a * 180.0 / M_PI);
        if (x < targetL)
            return -deg;
        else if (x > targetR)
            return deg;
        else
            return 0;
    }

    int powerToHover() const {
        return (dy >= 0) ? 3 : 4;
    }
};

int main() {
    MarsLander ship;

    int surfaceN;
    cin >> surfaceN;
    int landX, landY;
    int prevX = -1, prevY = -1;

    for (int i = 0; i < surfaceN; ++i) {
        cin >> landX >> landY;
        if (prevY != -1 && landY == prevY) {
            ship.setTarget(prevX, landX, landY);
        } else {
            prevX = landX;
            prevY = landY;
        }
    }

    while (true) {
        int X, Y, hSpeed, vSpeed, fuel, rotate, power;
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power;

        ship.init(X, Y, hSpeed, vSpeed, fuel, rotate, power);

        if (!ship.isOverTarget()) {
            if (ship.goesInWrongDirection() || ship.goesTooFastHorizontally()) {
                cout << ship.angleToSlow() << " 4" << endl;
            } else if (ship.goesTooSlowHorizontally()) {
                cout << ship.angleToAimTarget() << " 4" << endl;
            } else {
                cout << 0 << " " << ship.powerToHover() << endl;
            }
        } else {
            int altAboveFlat = Y - ship.targetY;
            if (altAboveFlat < 300) {
                int desiredAngle = 0;
                int desiredPower;

                if (vSpeed < -35)      desiredPower = 4;
                else if (vSpeed < -25) desiredPower = 3;
                else if (vSpeed < -15) desiredPower = 2;
                else                   desiredPower = 1;

                cout << desiredAngle << " " << desiredPower << endl;
            }
            else {
                if (ship.isFinishing()) {
                    cout << "0 3" << endl;
                } else if (ship.hasSafeSpeed()) {
                    cout << "0 2" << endl;
                } else {
                    cout << ship.angleToSlow() << " 4" << endl;
                }
            }
        }
    }
}
