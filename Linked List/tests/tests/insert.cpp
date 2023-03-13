#include "executable.h"
#include "box.h"
#include "List.h"

#include <list>
#include <iterator>
#include <iostream>

using namespace std;

TEST(insert) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x999ULL);

        {
            List<int> * ll = new List<int>();
       
            std::list<int> gt_ll;

            bool gt_walk_reversed = false,
                 walk_reversed = false;
            
            auto gt_pos = gt_ll.cbegin();
            auto pos = ll->cbegin();
            cout << "A" << endl;

            for(size_t i = 0; i < 5; i++) {
                size_t steps = t.range(gt_ll.size() + 1);
                int value = t.get<int>();
                
                cout << "!" << endl;
                pos = pace(*ll, pos, steps, walk_reversed);
                cout << "@" << endl;
                gt_pos = pace(gt_ll, gt_pos, steps, gt_walk_reversed);
                cout << "&" << endl;

                typename List<int>::iterator it_val;
                {
                    cout << "%" << endl;
                    Memhook mh;
                     cout << "#" << endl;
                    it_val = ll->insert(pos, value);
                    ASSERT_EQ(1ULL, mh.n_allocs());
                     cout << "B" << endl;
                }

                gt_ll.insert(gt_pos, value);

                // return value should point to item
                ASSERT_EQ(value, *it_val);

                // lists should be consistent
                {
                    std::cout << "Entering if" << std::endl;

                    ASSERT_EQ(gt_ll.size(), ll->size());

                    auto gt_it = gt_ll.cbegin();
                    auto it = ll->cbegin();
                     cout << "C" << endl;
                    
                    while(gt_it != gt_ll.cend())
                        ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");

                    while(gt_it != gt_ll.cbegin())
                        ASSERT_EQ_(*--gt_it, *--it,  "An inconsistency was found when iterating backward");
                }
            }
            cout << "D" << endl;
            delete ll;
             cout << "E" << endl;
        }

        {
            List<Box<int>> ll;

            auto pos = ll.cbegin();
            bool walk_reversed = false;

            for(size_t i = 0; i < n; i++) {
                size_t steps = t.range(i + 1);
                int value = t.get<int>();
                Box<int> newBox = value;

                pos = pace(ll, pos, steps, walk_reversed);

                Memhook mh;
                auto it_val = ll.insert(pos, std::move(newBox));

                ASSERT_EQ(i + 1, ll.size());
                // return value should point to inserted item
                ASSERT_EQ(value, **it_val);
                // only should allocate 1 node on the heap
                ASSERT_EQ(1ULL, mh.n_allocs());
            }
        }
    }
    
}
