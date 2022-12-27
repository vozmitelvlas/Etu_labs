# python
def find(pattern, line):
    q, x = 1e7 + 1, 666
    enters, line_size, pattern_size = [], len(line), len(pattern)
    coeffs = [1] * (pattern_size + 1)
    for i in range(pattern_size):
        coeffs[i + 1] = (coeffs[i] % q * x % q) % q

    def __hash(string, left, right):
        hash_value = 0
        for symbol_index in range(left, right):
            hash_value = (hash_value % q + ord(string[symbol_index]) % q * coeffs[symbol_index - left] % q) % q
        return hash_value

    def __compare(pattern, string, left, right):
        for i in range(left, right):
            if pattern[i - left] != string[i]:
                return False
        return True

    pattern_hash = __hash(pattern, 0, pattern_size)
    current = __hash(line, line_size - pattern_size, line_size)
    if current == pattern_hash and __compare(pattern, line, line_size - pattern_size, line_size):
        enters.append(line_size - pattern_size)
    for i in range(line_size - pattern_size - 1, -1, -1):
        current = (ord(line[i]) + (x % q * current % q) % q - (
                ord(line[i + pattern_size]) % q * coeffs[pattern_size] % q) % q) % q
        if current == pattern_hash:
            enters.append(i)
    return enters


if __name__ == '__main__':
    print(*list(reversed(find(input(), input()))))
