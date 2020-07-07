/* From: <https://old.reddit.com/r/Forth/comments/hi4b5c/i_made_a_forthish_thing_in_c_because_lockdown_is/> */
#include <array>
#include <charconv>
#include <iterator>
#include <iostream>
#include <string_view>

using Cell  = intptr_t;
using Array = std::array<Cell, 120>;

std::ostream_iterator<Cell> outIt (std::cout, " ");

struct Stack {
    Array storage;
    Array::iterator bos { storage.begin() };
    int32_t index { -1 };

    inline auto begin() const noexcept { return bos; }
    inline auto end()   const noexcept { return bos + index + 1; }

    inline Cell&  operator[](const int idx) noexcept { return storage[idx]; }
    inline Stack& operator()(Cell item)     noexcept { index++; bos[index] = item; return *this; }
    Stack() {}
};

int main(int argc, char* argv[]) {
    Stack st;

    #define si st.index
    #define sp st[si]

    auto str     = [&] (std::string_view s) { st((Cell)s.begin()); st(s.length()); };
    Cell i = 0;
    std::array<char, 10> toc_r;

    auto drop    = [&] { si--; };
    auto drop2   = [&] { si -= 2; };
    auto dup     = [&] { st[++si] = st[si-1]; };
    auto swap    = [&] { std::swap(st[si-1], sp); };
    auto add     = [&] { st[--si] += sp; };
    auto sub     = [&] { st[--si] -= sp; };
    auto mul     = [&] { st[--si] *= sp; };
    auto div     = [&] { st[--si] /= sp; };
    auto eq      = [&] { st[--si] = (st[si-1] == sp); };
    auto neq     = [&] { st[--si] = (st[si-1] != sp); };
    auto emit    = [&] { putchar((char)sp); drop(); };
    auto cr      = [&] { st('\n'); emit(); };
    auto type    = [&] { i = 0; while(i < sp) { putchar((char)((char*)st[si-1])[i]); i++; } drop2(); };
    auto dots    = [&] { str("( "); type(); std::copy(st.begin(), st.end(), outIt); st(')'); emit(); };
    auto convert = [&] { auto res = std::from_chars((char *)st[si-1], (char*)(sp + st[si-1]), st[si-1]); drop(); };
    auto to_str  = [&] { auto res = std::to_chars(toc_r.data(), toc_r.data() + toc_r.size(), sp); drop(); st((Cell)toc_r.data()); st(toc_r.size()); };

    st(1)(2); dots(); add(); cr(); dots(); cr();
    str("hello, world!"); type(); cr();

    return 0;
}
