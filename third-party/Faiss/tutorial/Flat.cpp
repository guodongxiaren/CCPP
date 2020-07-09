#include <cstdio>
#include <cstdlib>

#include <faiss/IndexFlat.h>

// 64-bit int
using idx_t = faiss::Index::idx_t;

int main() {
    int d = 64;      // dimension：维
    int nb = 100000; // 数据库大小
    int nq = 10000;  // query大小

    float *xb = new float[d * nb];
    float *xq = new float[d * nq];

    // xb理解成一个矩阵(nb行，d列)，虽然说一个一维数组
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < d; j++) {
            xb[d * i + j] = drand48();
        }
        xb[d * i] += i / 1000.;
    }

    faiss::IndexFlatL2 index(d); // 构造函数
    printf("is_trained = %s\n", index.is_trained ? "true" : "false");
    index.add(nb, xb); // 把向量(vector)添加到索引(index)
    printf("ntotal = %zd\n", index.ntotal);

    int k = 4;

    {
        // sanity check:合理性检查，搜索xb中前5个向量
        idx_t *I = new idx_t[k * 5];
        float *D = new float[k * 5];

        index.search(5, xb, k, D, I);

        printf("I=\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < k; j++) {
                printf("%5zd ", I[i * k + j]);
            }
            printf("\n");
        }
        printf("D=\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < k; j++) {
                printf("%7g ", D[i * k + j]);
            }
            printf("\n");
        }

        delete [] I;
        delete [] D;
    }

    {
        // 搜索xq
        idx_t *I = new idx_t[k * nq];
        float *D = new float[k * nq];

        index.search(nq, xb, k, D, I);

        printf("I(5 fist results)=\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < k; j++) {
                printf("%5zd ", I[i * k + j]);
            }
            printf("\n");
        }
        printf("I(5 last results)=\n");
        for (int i = nq - 5; i < nq; i++) {
            for (int j = 0; j < k; j++) {
                printf("%zd ", I[i * k + j]);
            }
            printf("\n");
        }

        delete [] I;
        delete [] D;
    }

    delete [] xb;
    delete [] xq;

    return 0;
}

