#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>

const int    POP_SIZE       = 20;
const double MUTATION_RATE  = 0.001;
const int    RESTARTS       = 3;
const double TIME_LIMIT_SEC = 8.5;

using ll = long long;
using Clock = std::chrono::steady_clock;
Clock::time_point g_start;

double elapsed() {
    return std::chrono::duration<double>(Clock::now() - g_start).count();
}

struct Individual {
    std::vector<int8_t> bits;
    ll fitness = 0;
    ll weight  = 0;
};

Individual greedySwapInit(int N, ll W,
                          const std::vector<ll>& values,
                          const std::vector<ll>& weights,
                          const std::vector<int>& order,
                          double noiseP,
                          std::mt19937& rng)
{
    std::uniform_real_distribution<double> rnd(0.0, 1.0);
    Individual ind;
    ind.bits.assign(N, 0);

    // Шаг 1: жадное заполнение по c/w с шумом
    for (int i = 0; i < N; ++i) {
        int idx = order[i];
        if (rnd(rng) < noiseP) continue;
        if (ind.weight + weights[idx] <= W) {
            ind.bits[idx]  = 1;
            ind.fitness   += values[idx];
            ind.weight    += weights[idx];
        }
    }

    // Шаг 2: swap-улучшение — заменяем взятый на невзятый если выгодно
    for (int i = 0; i < N; ++i) {
        int out_idx = order[i];
        if (!ind.bits[out_idx]) continue;

        for (int j = 0; j < N; ++j) {
            int in_idx = order[j];
            if (ind.bits[in_idx]) continue;

            ll newWeight = ind.weight  - weights[out_idx] + weights[in_idx];
            ll newValue  = ind.fitness - values[out_idx]  + values[in_idx];

            if (newWeight <= W && newValue > ind.fitness) {
                ind.bits[out_idx] = 0;
                ind.bits[in_idx]  = 1;
                ind.weight        = newWeight;
                ind.fitness       = newValue;
                break;
            }
        }
    }

    return ind;
}

Individual mutateInd(const Individual& parent, int N, double mutRate,
                     const std::vector<ll>& values,
                     const std::vector<ll>& weights,
                     std::mt19937& rng)
{
    std::uniform_real_distribution<double> rnd(0.0, 1.0);
    Individual child = parent;
    for (int i = 0; i < N; ++i) {
        if (rnd(rng) < mutRate) {
            child.bits[i] ^= 1;
            if (child.bits[i]) { child.weight += weights[i]; child.fitness += values[i]; }
            else               { child.weight -= weights[i]; child.fitness -= values[i]; }
        }
    }
    return child;
}

void repair(Individual& ind, int N, ll W,
            const std::vector<ll>& values,
            const std::vector<ll>& weights,
            const std::vector<int>& order)
{
    for (int j = N - 1; j >= 0 && ind.weight > W; --j) {
        int i = order[j];
        if (ind.bits[i]) {
            ind.bits[i]  = 0;
            ind.weight  -= weights[i];
            ind.fitness -= values[i];
        }
    }
}

int main() {
    g_start = Clock::now();
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N; ll W;
    std::cin >> N >> W;

    std::vector<ll> values(N), weights(N);
    for (int i = 0; i < N; ++i) std::cin >> values[i] >> weights[i];

    std::vector<int> order(N);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return values[a] * weights[b] > values[b] * weights[a];
    });

    std::mt19937 rng(std::random_device{}());
    Individual best; best.fitness = -1;

    double timePerRestart = TIME_LIMIT_SEC / RESTARTS;

    for (int restart = 0; restart < RESTARTS && elapsed() < TIME_LIMIT_SEC; ++restart) {
        double deadline = (restart + 1) * timePerRestart;

        std::vector<Individual> pop(POP_SIZE);
        pop[0] = greedySwapInit(N, W, values, weights, order, 0.0, rng);
        for (int p = 1; p < POP_SIZE; ++p) {
            double noise = 0.05 * p / POP_SIZE * (restart + 1);
            pop[p] = greedySwapInit(N, W, values, weights, order, noise, rng);
        }

        for (auto& ind : pop)
            if (ind.fitness > best.fitness) best = ind;

        while (elapsed() < deadline) {
            for (int p = 0; p < POP_SIZE; ++p) {
                Individual child = mutateInd(pop[p], N, MUTATION_RATE,
                                             values, weights, rng);
                repair(child, N, W, values, weights, order);
                if (child.fitness >= pop[p].fitness)
                    pop[p] = std::move(child);
                if (pop[p].fitness > best.fitness)
                    best = pop[p];
            }
        }
    }

    std::cout << best.fitness << '\n';
    bool first = true;
    for (int i = 0; i < N; ++i) {
        if (best.bits[i]) {
            if (!first) std::cout << ' ';
            std::cout << (i + 1);
            first = false;
        }
    }
    std::cout << '\n';
    return 0;
}
