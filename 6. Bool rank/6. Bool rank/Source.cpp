#include <stdarg.h>
#include <iostream>

class BoolRank
{
private:
    //friend std::ostream& operator<<(std::ostream& out, const BoolRank& bRank);
public:
    BoolRank(unsigned char& element, const int bitPos) : m_element(element)
    {
        if (bitPos >= 0 && bitPos < 8)
        {
            m_bitPos = bitPos;
        }
        else
        {
            throw std::out_of_range("BoolRank::BoolRank(char&, int), out of the memory block");
        }
    }

    int value() const;

    BoolRank& operator&=(const int val);
    BoolRank& operator|=(const int val);
    BoolRank& operator^=(const int val);

    int operator&(const bool val) const;
    int operator|(const bool val) const;
    int operator^(const bool val) const;
    int operator~() const;

    bool operator==(const int value) const;
    bool operator!=(const int value) const;

    explicit operator int() const
    {
        return value();
    }

    explicit operator char() const
    {
        return value();
    }

    operator bool() const
    {
        return value();
    }

    BoolRank& operator=(const int i);
private:
    unsigned char& m_element;
    int m_bitPos;
};

inline std::ostream& operator<<(std::ostream& out, const BoolRank& bRank)
{
    out << (bool)bRank;
    return out;
}

int BoolRank::value() const
{
    unsigned char mask = 1 << m_bitPos;
    return m_element & mask;
}

BoolRank& BoolRank::operator&=(const int val)
{
    unsigned char mask = 1 << m_bitPos;
    if (!val)
    {
        m_element &= (~mask);
    }
    return *this;
}

BoolRank& BoolRank::operator|=(const int val)
{
    unsigned char mask = 1 << m_bitPos;
    m_element |= mask;
    return *this;
}

BoolRank& BoolRank::operator^=(const int val)
{
    unsigned char mask = 1 << m_bitPos;
    if (*this != val)
    {
        m_element |= mask;
    }
    else
    {
        m_element &= (~mask);
    }

    return *this;
}

int BoolRank::operator&(const bool val) const
{
    unsigned char mask = 1 << m_bitPos;
    if (m_element & mask)
    {
        return val;
    }
    return 0;
}

int BoolRank::operator|(const bool val) const
{
    unsigned char mask = 1 << m_bitPos;
    if (m_element & mask)
    {
        return 1;
    }
    return val;
}

int BoolRank::operator^(const bool val) const
{
    unsigned char mask = 1 << m_bitPos;
    if (m_element & mask)
    {
        return !val;
    }
    return val;
}

int BoolRank::operator~() const
{
    unsigned char mask = 1 << m_bitPos;
    if (m_element & mask)
    {
        return 0;
    }
    return 1;
}

bool BoolRank::operator==(const int value) const
{
    if ((bool)this->value() == (bool)value)
    {
        return true;
    }
    return false;
}

bool BoolRank::operator!=(const int value) const
{
    return !operator==(value);
}

BoolRank& BoolRank::operator=(const int i)
{
    if (i != 0 && i != 1)
    {
        throw std::out_of_range("BoolRank::operator=(int)\n");
    }
    unsigned char mask = 1 << m_bitPos;
    if (*this != i)
    {
        if (!(m_element & mask))
        {
            (m_element) |= mask;
        }
        else
        {
            (m_element) &= (~mask);
        }
    }
    return *this;
}

class BoolVector
{
private:
    int roundToPowerOfTwo(const int n);
    bool convertToBool(const char ch);
    //void _setBitCollection(const int size, va_list Args);

    friend std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec);
    friend std::istream& operator>>(std::istream& stream, BoolVector& bvec);
public:
    BoolVector();
    explicit BoolVector(const int size);
    explicit BoolVector(const int size, const bool var);
    explicit BoolVector(const char* boolArr);
    BoolVector(const char* boolArr, const int size);
    BoolVector(const BoolVector& other);
    ~BoolVector() { delete[] m_data; }

    void inverse();					   // inverses whole boolean vector
    void inverse(const int bitPosition); // inverse certain bit
    void inverse(const int bitPosition, const int count);
    void setBit(const int value, const int bitPosition);  // set a certain bit
    void setBit(const bool value, const int startFrom, int count);	   // setting collection of bit
    void set(const bool var);
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacity; }
    int getByte(int byte) { return m_data[byte]; }
    int weight() const;

    BoolVector operator=(const BoolVector& other);
    BoolRank operator[](const int bitPosition);
    const BoolRank operator[](const int bitPosition) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector& operator|=(const BoolVector& other);
    BoolVector& operator^=(const BoolVector& other);
    BoolVector& operator<<=(const int shiftNumber);
    BoolVector& operator>>=(const int shiftNumber);
    BoolVector operator&(const BoolVector& other) const;
    BoolVector operator|(const BoolVector& other) const;
    BoolVector operator^(const BoolVector& other) const;
    BoolVector operator~() const;
    BoolVector operator<<(const int shiftNumber) const;
    BoolVector operator>>(const int shiftNumber) const;
private:
    unsigned char* m_data = nullptr;
    int m_size = 0;
    int m_capacity = 0;
};

inline std::ostream& operator<<(std::ostream& stream, const BoolVector& bvec)
{
    for (int i = bvec.m_size - 1; i >= 0; --i)
    {
        stream << bvec[i];
    }
    return stream;
}

inline std::istream& operator>>(std::istream& stream, BoolVector& bvec)
{
    char* str = new char[(bvec.m_size + 1)];
    bvec.m_data[bvec.m_capacity - 1] = 0;
    stream >> str;
    bvec = BoolVector(str, bvec.m_size);

    return stream;
}

BoolVector::BoolVector() : m_data(new unsigned char[1]), m_size(8), m_capacity(1)
{
    m_data[0] = 0;
}

BoolVector::BoolVector(const int size)
{
    m_size = size;
    m_capacity = roundToPowerOfTwo(size) / 8;
    m_data = new unsigned char[m_capacity];

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = 0;
    }
}

BoolVector::BoolVector(const int size, const bool var)
{
    m_size = size;
    m_capacity = m_size % 8 != 0 ? m_size / 8 + 1 : m_size / 8;
    m_data = new unsigned char[m_capacity];
    m_data[m_capacity - 1] = 0;
    int i;

    unsigned char byteVal = 0;
    if (var)
    {
        byteVal = ~byteVal;
    }

    for (i = 0; i < m_capacity; ++i)
    {
        m_data[i] = byteVal;
    }

    unsigned char mask = ~0;
    mask >>= (8 - m_size % 8);
    m_data[m_capacity - 1] &= mask;
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_data = new unsigned char[other.m_capacity];
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = other.m_data[i];
    }
}

BoolVector::BoolVector(const char* boolArr)
{
    m_size = (int)strlen(boolArr);
    m_capacity = (m_size % 8 == 0) ? m_size / 8 : m_size / 8 + 1;
    m_data = new unsigned char[m_capacity];

    m_data[m_capacity - 1] = 0;

    for (int i = 0; i < m_size; ++i)
    {
        try
        {
            if (convertToBool(boolArr[m_size - i - 1]))
            {
                setBit(1, i);
            }
            else
            {
                setBit(0, i);
            }
        }
        catch (const std::string& str)
        {
            std::cout << str;
        }
    }
}

BoolVector::BoolVector(const char* boolArr, const int size)
{
    m_size = size;
    m_capacity = (m_size % 8 == 0) ? m_size / 8 : m_size / 8 + 1;
    m_data = new unsigned char[m_capacity];

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = 0;
    }

    int strSize = (int)strlen(boolArr);
    for (int i = 0; i < m_size && i < strSize; ++i)
    {
        try
        {
            if (convertToBool(boolArr[i]))
            {
                setBit(1, i);
            }
            else
            {
                setBit(0, i);
            }
        }
        catch (const std::string& str)
        {
            std::cout << str;
        }
    }
}

void BoolVector::inverse()
{
    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = ~m_data[i];
    }

    unsigned char mask = (1 << (m_size % 8)) - 1;
    int bytePosition = m_size / 8;
    m_data[bytePosition] = m_data[bytePosition] & mask;
}

void BoolVector::inverse(const int bitPosition)
{
    int bytePosition = bitPosition / 8;
    unsigned char mask = 1 << (bitPosition % 8);

    if (!(m_data[bytePosition] & mask))
    {
        m_data[bytePosition] |= mask;
    }
    else
    {
        m_data[bytePosition] &= (~mask);
    }
}

void BoolVector::inverse(const int startFrom, const int count)
{
    if (startFrom >= m_size || startFrom < 0 || startFrom + count > m_size)
    {
        throw std::out_of_range("index out of memory");
    }
    else if (count == 0)
    {
        return;
    }

    unsigned char mask = ~0;
    mask <<= startFrom % 8;

    if (startFrom / 8 == ((startFrom + count) / 8))
    {
        unsigned char otherMask = ~0;
        otherMask >>= 8 - (startFrom + count) % 8;

        mask &= otherMask;
        m_data[startFrom / 8] ^= mask;
    }
    else
    {
        m_data[startFrom / 8] ^= mask;

        mask = ~0;
        mask >>= 8 - (startFrom + count) % 8;
        m_data[(startFrom + count) / 8] ^= mask;

        for (int i = startFrom / 8 + 1; i < (startFrom + count) / 8; ++i)
        {
            m_data[i] = ~m_data[i];
        }
    }
}

void BoolVector::setBit(const int value, const int bitPosition)
{
    operator[](bitPosition) = (bool)value;
}

void BoolVector::setBit(const bool value, const int startFrom, int count)
{
    if (startFrom >= m_size || startFrom < 0 || startFrom + count > m_size)
    {
        throw std::out_of_range("index out of memory");
    }
    else if (count == 0)
    {
        return;
    }

    unsigned char mask = ~0;
    mask <<= startFrom % 8;

    if (startFrom / 8 == ((startFrom + count) / 8))
    {
        unsigned char otherMask = ~0;
        otherMask >>= (8 - (count + startFrom) % 8);
        mask &= otherMask;
        if (value)
        {
            m_data[startFrom / 8] |= mask;
        }
        else
        {
            mask = ~mask;
            m_data[startFrom / 8] &= mask;
        }
    }
    else
    {
        unsigned char byteVal = 0;
        if (value)
        {
            m_data[startFrom / 8] |= mask;

            mask = ~0;
            mask >>= (8 - (count + startFrom) % 8);
            m_data[(startFrom + count) / 8] |= mask;
            byteVal = ~byteVal;
        }
        else
        {
            mask = ~mask;
            m_data[startFrom / 8] &= mask;

            mask = ~0;
            mask <<= (count + startFrom) % 8;
            m_data[(startFrom + count) / 8] &= mask;
        }

        for (int i = startFrom / 8 + 1; i < (startFrom + count) / 8; ++i)
        {
            m_data[i] = byteVal;
        }
    }


}

void BoolVector::set(const bool var)
{
    m_data[m_capacity - 1] = 0;
    int i;

    unsigned char byteVal = 0;
    if (var)
    {
        byteVal = ~byteVal;
    }

    for (i = 0; i < m_capacity; ++i)
    {
        m_data[i] = byteVal;
    }

    unsigned char mask = ~0;
    mask >>= (8 - m_size % 8);
    m_data[m_capacity - 1] &= mask;
}

int BoolVector::weight() const
{
    int weight = 0;

    for (int i = 0; i < m_size; ++i)
    {
        if ((int)operator[](i))
        {
            weight++;
        }
    }
    return weight;
}

int BoolVector::roundToPowerOfTwo(const int n)
{
    int v = n;

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    return ++v;
}

bool BoolVector::convertToBool(const char ch)
{
    if (ch == 49)
    {
        return true;
    }
    else if (ch == 48)
    {
        return false;
    }
    else
    {
        throw std::string("BoolVector::convertToBool(char*) Cannot covert character to bool");
    }
}

BoolRank BoolVector::operator[](const int bitPosition)
{
    BoolRank data(m_data[bitPosition / 8], (bitPosition % 8));
    return data;
}

const BoolRank BoolVector::operator[](const int bitPosition) const
{
    BoolRank data(m_data[bitPosition / 8], (bitPosition % 8));
    return data;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
    int minCap = m_capacity;
    if (m_capacity > other.m_capacity)
    {
        minCap = other.m_capacity;
        for (int i = minCap; i < m_capacity; i++)
        {
            m_data[i] = 0;
        }
    }

    for (int i = 0; i < minCap - 1; ++i)
    {
        m_data[i] &= other.m_data[i];
    }

    int minSize = m_size > other.m_size ? other.m_size : m_size;
    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;
    m_data[minCap - 1] &= other.m_data[minCap - 1];
    m_data[minCap - 1] &= mask;

    return *this;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
    int minCapacity = m_capacity;
    int minSize = m_size;
    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;

    if (m_capacity > other.m_capacity)
    {
        minCapacity = other.m_capacity;
        mask = ~0;
    }

    for (int i = 0; i < minCapacity; ++i)
    {
        m_data[i] |= other.m_data[i];
    }

    m_data[minCapacity - 1] &= mask;
    return *this;
}

BoolVector& BoolVector::operator^=(const BoolVector& other)
{
    int minCapacity = m_capacity;
    int minSize = m_size;

    if (m_capacity > other.m_capacity)
    {
        minCapacity = other.m_capacity;
        minSize = other.m_size;
    }
    for (int i = 0; i < minCapacity - 1; ++i)
    {
        m_data[i] ^= other.m_data[i];
    }

    unsigned char mask = ~0;
    mask >>= 8 - minSize % 8;
    unsigned char saveByte = other.m_data[minCapacity - 1] & mask;
    m_data[minCapacity - 1] ^= saveByte;
    return *this;
}

BoolVector& BoolVector::operator<<=(const int shiftNumber)
{
    if (shiftNumber < 0)
    {
        return operator>>=(-shiftNumber);
    }

    int shiftByte = shiftNumber / 8;
    if (shiftByte < m_capacity)
    {
        int shiftBit = shiftNumber % 8;

        unsigned char saveByte;

        unsigned char mask = ~0;
        mask <<= (8 - shiftBit);
        for (int i = m_capacity - 1; i >= shiftByte; --i)
        {
            m_data[i] = m_data[i - shiftByte] << shiftBit;
            if (i != shiftByte)
            {
                saveByte = m_data[i - 1 - shiftByte] & mask;
                saveByte >>= (8 - shiftBit);

                m_data[i] |= saveByte;
            }

        }
        mask = ~0;
        mask >>= 8 - (m_size % 8);
        m_data[m_capacity - 1] &= mask;
    }
    else shiftByte = m_capacity;

    for (int i = 0; i < shiftByte; i++)
    {
        m_data[i] = 0;
    }

    return *this;
}

BoolVector& BoolVector::operator>>=(const int shiftNumber)
{
    if (shiftNumber < 0)
    {
        return operator<<=(-shiftNumber);
    }

    int shiftByte = shiftNumber / 8;

    if (shiftByte < m_capacity)
    {
        int shiftBit = shiftNumber % 8;

        unsigned char saveByte;

        unsigned int mask = ~0;
        mask >>= (8 - shiftBit);

        for (int i = 0; i < m_capacity - shiftByte; ++i)
        {
            m_data[i] = m_data[i + shiftByte] >> shiftBit;

            if (i != m_capacity - 1 - shiftByte)
            {
                saveByte = m_data[i + 1 + shiftByte] & mask;
                saveByte <<= (8 - shiftBit);

                m_data[i] |= saveByte;
            }
        }
    }
    else
    {
        shiftByte = m_capacity;
    }

    for (int i = m_capacity - shiftByte; i < m_capacity; i++)
    {
        m_data[i] = 0;
    }

    return *this;
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
    BoolVector conjunction(*this);
    conjunction &= other;
    return conjunction;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
    BoolVector disjunction(*this);
    disjunction |= other;
    return disjunction;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    BoolVector XOR(*this);
    XOR ^= other;
    return XOR;
}

BoolVector BoolVector::operator~() const
{
    BoolVector NOT(*this);
    NOT.inverse();
    return NOT;
}

BoolVector BoolVector::operator=(const BoolVector& other)
{
    if (this == &other) return *this;

    if (m_capacity != other.m_capacity)
    {
        delete[] m_data;
        m_data = new unsigned char[other.m_capacity];
        m_capacity = other.m_capacity;
    }
    m_size = other.m_size;

    for (int i = 0; i < m_capacity; ++i)
    {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

BoolVector BoolVector::operator<<(const int shiftNumber) const
{
    BoolVector other(*this);
    other <<= shiftNumber;
    return other;
}

BoolVector BoolVector::operator>>(const int shiftNumber) const
{
    BoolVector other(*this);
    other >>= shiftNumber;
    return other;
}

class BoolMatrix
{
private:
    friend std::ostream& operator<<(std::ostream& stream, const BoolMatrix& bMatr);
    friend std::istream& operator>>(std::istream& stream, const BoolMatrix& bMatr);
public:
    BoolMatrix();
    BoolMatrix(const int row, const int column, const bool value);
    BoolMatrix(const char** str, const int row, const int column);
    BoolMatrix(const BoolMatrix& other);
    ~BoolMatrix();

    int weight() const;
    int weight(const int row) const;

    BoolVector disjunction() const;
    BoolVector conjunction() const;

    void inverse(const int row, const int bitPos);
    void inverse(const int row, const int bitPos, const int count);
    void set(const bool value, const int row, const int bitPos);
    void set(const bool value, const int row, const int bitPos, const int count);

    BoolMatrix operator=(const BoolMatrix& other);

    BoolVector& operator[](const int row);
    const BoolVector operator[](const int row) const;
    BoolMatrix& operator&=(const BoolMatrix& other);
    BoolMatrix& operator|=(const BoolMatrix& other);
    BoolMatrix& operator^=(const BoolMatrix& other);
    BoolMatrix operator&(const BoolMatrix& other) const;
    BoolMatrix operator|(const BoolMatrix& other) const;
    BoolMatrix operator^(const BoolMatrix& other) const;
    BoolMatrix operator~() const;
private:
    BoolVector* m_matr;
    int m_row;
    int m_column;
};

inline std::ostream& operator<<(std::ostream& stream, const BoolMatrix& bMatr)
{
    for (int i = 0; i < bMatr.m_row; ++i)
    {
        stream << bMatr.m_matr[i] << std::endl;
    }
    return stream;
}

inline std::istream& operator>>(std::istream& stream, const BoolMatrix& bMatr)
{
    for (int i = 0; i < bMatr.m_row; ++i)
    {
        try {
            stream >> bMatr.m_matr[i];
        }
        catch (...)
        {
            std::cout << "111";
        }
    }
    return stream;
}

BoolMatrix::BoolMatrix()
{
    m_row = 8;
    m_column = 8;
    m_matr = new BoolVector[m_row];

    for (int i = 0; i < m_row; ++i)
    {
        m_matr[i] = BoolVector(m_column, 0);
    }
}

BoolMatrix::BoolMatrix(const int row, const int column, const bool value)
{
    m_row = row;
    m_column = column;
    m_matr = new BoolVector[m_row];
    for (int i = 0; i < m_row; ++i)
    {
        m_matr[i] = BoolVector(m_column, value);
    }
}

BoolMatrix::BoolMatrix(const char** str, const int row, const int column)
{
    m_row = row;
    m_column = column;
    m_matr = new BoolVector[m_row];

    for (int i = 0; i < m_row; ++i)
    {
        m_matr[i].set(0);
    }

    for (int i = 0; i < row; ++i)
    {
        m_matr[i] = BoolVector(str[i], m_column);
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix& other)
{
    m_matr = new BoolVector[other.m_row];
    m_row = other.m_row;
    m_column = other.m_column;

    for (int i = 0; i < m_row; ++i)
    {
        m_matr[i] = other.m_matr[i];
    }
}

BoolMatrix::~BoolMatrix()
{
    delete[] m_matr;
}

int BoolMatrix::weight() const
{
    int weight = 0;
    for (int i = 0; i < m_row; ++i)
    {
        weight += m_matr[i].weight();
    }
    return weight;
}

int BoolMatrix::weight(const int row) const
{
    if (row < 0 || row >= m_row)
    {
        throw std::out_of_range("bla bla bla");
    }

    return m_matr[row].weight();
}

BoolVector BoolMatrix::disjunction() const
{
    BoolVector disjunction(m_matr[0]);
    for (int i = 1; i < m_row; ++i)
    {
        disjunction |= m_matr[i];
    }
    return disjunction;
}

BoolVector BoolMatrix::conjunction() const
{
    BoolVector conjunction(m_matr[0]);
    for (int i = 1; i < m_row; ++i)
    {
        conjunction &= m_matr[i];
    }
    return conjunction;
}

void BoolMatrix::inverse(const int row, const int bitPos)
{
    if (row < 0 || row >= m_row)
    {
        throw std::out_of_range("out of memory block");
    }
    m_matr[row].inverse(bitPos);
}

void BoolMatrix::inverse(const int row, const int bitPos, const int count)
{
    if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
    {
        throw std::out_of_range("out of memory block");
    }
    m_matr[row].inverse(bitPos, count);
}

void BoolMatrix::set(const bool value, const int row, const int bitPos)
{
    if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
    {
        throw std::out_of_range("out of memory block");
    }
    m_matr[row].setBit(value, bitPos);
}

void BoolMatrix::set(const bool value, const int row, const int bitPos, const int count)
{
    if (row < 0 || row >= m_row || bitPos < 0 || bitPos >= m_column)
    {
        throw std::out_of_range("out of memory block");
    }
    m_matr[row].setBit(value, bitPos, count);
}

BoolMatrix BoolMatrix::operator=(const BoolMatrix& other)
{
    if (this == &other) return *this;

    if (m_row != other.m_row || m_column != other.m_column)
    {
        delete[] m_matr;
        m_matr = new BoolVector[other.m_row];
        m_row = other.m_row;
        m_column = other.m_column;
    }

    for (int i = 0; i < m_column; ++i)
    {
        m_matr[i] = other.m_matr[i];
    }
    return *this;
}

BoolVector& BoolMatrix::operator[](const int row)
{
    if (row < 0 || row >= m_row)
    {
        throw std::out_of_range("bla bla bla");
    }
    return m_matr[row];
}

const BoolVector BoolMatrix::operator[](const int row) const
{
    BoolVector data(m_matr[row]);
    return data;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other)
{
    int minRow = m_row > other.m_row ? other.m_row : m_row;
    for (int i = 0; i < minRow; ++i)
    {
        m_matr[i] &= other.m_matr[i];
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other)
{
    int minRow = m_row > other.m_row ? other.m_row : m_row;
    for (int i = 0; i < minRow; ++i)
    {
        m_matr[i] |= other.m_matr[i];
    }
    return *this;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other)
{
    int minRow = m_row > other.m_row ? other.m_row : m_row;
    for (int i = 0; i < minRow; ++i)
    {
        m_matr[i] ^= other.m_matr[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const
{
    BoolMatrix conjuction(*this);
    conjuction &= other;
    return conjuction;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const
{
    BoolMatrix disjuction(*this);
    disjuction &= other;
    return disjuction;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const
{
    BoolMatrix XOR(*this);
    XOR &= other;
    return XOR;
}

BoolMatrix BoolMatrix::operator~() const
{
    BoolMatrix NOT(*this);
    for (int i = 0; i < m_row; ++i)
    {
        NOT.m_matr[i].operator~();
    }

    return NOT;
}

int _testShift(const int length = 100, const int offset = 1)
{
    using std::cout;
    using std::endl;

    BoolVector vector1(length, 1);
    BoolVector vector2(length, 1);
    for (int i = 0; i <= length; i += offset) {
        vector1 = (vector2 << i);
        cout << vector1 << endl;
    }

    for (int i = 0; i <= length; i += offset) {
        vector1 = (vector2 >> i);
        cout << vector1 << endl;
    }

    return 1;
}

void testShift()
{
    for (int offset = 1; offset < 10; offset += 2) {
        _testShift(100, offset);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int testSetBit()
{
    BoolVector vector(100, 1);
    for (int i = 0; i < 100; i++)
    {
        vector.setBit(0, 99 - i, 1);
        std::cout << i << "\t";
        std::cout << vector << std::endl;
        vector.set(1);
    }
    return 1;
}

void testConjuction()
{
    BoolVector vector1("100101010101001");
    BoolVector vector2("1101001");

    vector1 &= vector2;
    std::cout << vector1 << " " << vector1.getByte(0);
    return;
}

void testDisjuction()
{
    BoolVector vector1("000101010101001");
    BoolVector vector2("10110");

    vector1 ^= vector2;
    std::cout << vector1 << " " << vector1.getByte(1);
    return;
}

int main()
{
    //testConjuction();
    //return 0;
    BoolMatrix matr(10, 10, 0);
    matr.inverse(0, 0, 9);
    //std::cout << matr;

    const char* arr[] = { "01010010", "00000111111", "001100110011" };
    BoolMatrix m(arr, 3, 8);
    std::cout << m;
    std::cin >> m;
    std::cout << m;
    return 0;
}