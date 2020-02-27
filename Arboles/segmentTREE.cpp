#include <vector>
#include <limits>
#include <iostream>

using namespace std;

class SegmentTree {
public:
    SegmentTree(int count) {
        n = count;
        data.assign(2 * n, 0);
    }
    void mostrar(){
        for (int i = 0; i < 2*n; ++i)
        {
            cout << data[i]<<" ";
        }
        cout << endl;
    }

    SegmentTree(std::vector<int> const &values) {
        n = values.size();
        data.resize(2 * n);
        std::copy(values.begin(), values.end(), &data[0] + n);
        //mostrar();
        for (int idx = n - 1; idx > 0; idx--){
            data[idx] = data[2 * idx] + data[2 * idx + 1];
           // mostrar();
            //cout << endl;
        }

    }

    void update(int idx, int value) {
        idx += n;
        data[idx] = value;

        while (idx > 1) {
            idx /= 2;
            data[idx] = data[2 * idx] + data[2 * idx + 1];
        }
    }

    int sum(int left, int right) { // interval [left, right)
        int ret = 0;
        mostrar();
        left += n;
        //cout << "izquierda + n: "<<left<<endl;

        right += n;
        //cout << "derecha + n: "<<right<<endl;

        while (left < right) {
            if (left & 1) {
                ret += data[left++];
                //cout << "ret izquierda: "<<ret<<endl;
                //mostrar();
            }
            if (right & 1) {
                ret += data[--right];
               // cout << "ret derecha: "<<ret<<endl;
                //mostrar();
            }
            left >>= 1;
            //cout << "izquierda: "<<left<<endl;
            right >>= 1;
            //cout << "derecha: "<<right<<endl;
        }
        return ret;
    }

private:
    int n;
    std::vector<int> data;
};

int main(int argc, char const *argv[])
{
    SegmentTree a({2,5,3,4,6,7,8,3,9});
    a.mostrar();
    cout << "suma del rango: " << a.sum(4,7)<<endl;
    return 0;
}