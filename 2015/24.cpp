#include "../test.hpp"

namespace {

using namespace boost::ut;

using WeightsT = std::vector<unsigned>;

class Arranger
{
public:
    Arranger(const WeightsT &weights)
        : _weights{weights}
    {
        unsigned sum = std::accumulate(begin(weights), end(weights), 0u,
                                       [](unsigned a, unsigned b) { return a + b; });
        expect(0_u == sum % 3);
        _target = sum / 3;
        _max_length = weights.size() / 3;
        std::sort(begin(_weights), end(_weights),
                  [](unsigned a, unsigned b) { return b < a; });
    }

    uint64_t Compact()
    {
        ExploreForward(0, 0);
        return _qe;
    }

private:
    WeightsT _weights;
    unsigned _target;
    size_t _max_length;
    size_t _min_length = std::numeric_limits<size_t>::max();
    uint64_t _qe = std::numeric_limits<uint64_t>::max();

    void ExploreForward(size_t length, unsigned partial_sum)
    {
        if (length > _max_length)
            return;
        if (length > _min_length)
            return;
        if (partial_sum > _target)
            return;
        if (partial_sum == _target)
        {
            // Check if can split to the side compartments.
            if (CheckCanSplit(length, 0))
            {
                auto calcQe = [this, length]() {
                    return std::accumulate(begin(_weights), begin(_weights) + length, 1ull,
                                           [](auto a, auto b) { return a * b; });
                };
                if (length < _min_length)
                {
                    _min_length = length;
                    _qe = calcQe();
                }
                else if (length == _min_length)
                {
                    auto qe = calcQe();
                    if (qe < _qe)
                        _qe = qe;
                }
            }
            else
            {
                return;
            }
            
            return;
        }

        // Make sure to check the sequence is descending to exclude repeating permutations.
        unsigned prev = length > 0 ? _weights[length-1] : std::numeric_limits<unsigned>::max();

        // Try all the rest items
        for (size_t i = length; i < _weights.size(); ++i)
        {
            if (prev < _weights[i])
                continue;
            std::swap(_weights[i], _weights[length]);
            ExploreForward(length + 1, partial_sum + _weights[length]);
            std::swap(_weights[i], _weights[length]);
        }
    }

    bool CheckCanSplit(size_t length, unsigned partial_sum)
    {
        if (partial_sum == _target)
            return true;
        if (partial_sum > _target)
            return false;
        for (size_t i = length; i < _weights.size(); ++i)
        {
            std::swap(_weights[i], _weights[length]);
            bool res = CheckCanSplit(length + 1, partial_sum + _weights[length]);
            std::swap(_weights[i], _weights[length]);
            if (res)
                return true;
        }
        return false;
    }
};

suite s = [] {
    "2015-24"_test = [] {
        //{
        //    Arranger test{{1,2,3,4,5,7,8,9,10,11}};
        //    expect(99_u == test.Compact());
        //}

        const WeightsT TASK_INPUT{
            1, 2, 3, 7, 11, 13, 17, 19, 23, 31,
            37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
            79, 83, 89, 97, 101, 103, 107, 109, 113,
        };
        Printer::Print(__FILE__, "1", Arranger{TASK_INPUT}.Compact());
    };
};

} //namespace;