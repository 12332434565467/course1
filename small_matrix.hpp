struct SmallMat
{
    T v[M * N];

    constexpr T& operator[](
        std::size_t i, std::size_t j) noexcept
    {
        assert(i < M && j < N);
        return v[i * N + j];
    }

    constexpr T operator[](
        std::size_t i, std::size_t j) const noexcept
    {
        assert(i < M && j < N);
        return v[i * N + j];
    }

    constexpr T const* data() const noexcept
    {
        return v;
    }
};

template<std::size_t M, std::size_t N,
         std::size_t P, typename T>
constexpr SmallMat<M, P, T> operator*(
    SmallMat<M, N, T> const& a,
    SmallMat<N, P, T> const& b) noexcept
{
    SmallMat<M, P, T> result{};

    for (std::size_t i = 0; i < M; ++i)
        for (std::size_t j = 0; j < P; ++j)
            for (std::size_t k = 0; k < N; ++k)
                result[i, j] += a[i, k] * b[k, j];

    return result;
}

template<std::size_t M, std::size_t N, typename T>
constexpr SmallVec<M, T> operator*(
    SmallMat<M, N, T> const& a,
    SmallVec<N, T> const& b) noexcept
{
    SmallVec<M, T> result{};

    for (std::size_t i = 0; i < M; ++i)
        for (std::size_t j = 0; j < N; ++j)
            result[i] += a[i, j] * b[j];

    return result;
}

template<std::size_t M, std::size_t N, typename T>
constexpr SmallMat<N, M, T> transpose(
    SmallMat<M, N, T> const& a) noexcept
{
    SmallMat<N, M, T> result{};

    for (std::size_t i = 0; i < M; ++i)
        for (std::size_t j = 0; j < N; ++j)
            result[j, i] = a[i, j];

    return result;
}

template<class Matrix>
constexpr Matrix make_identity() noexcept
{
    Matrix result{};

    []<std::size_t N, typename T>(
        SmallMat<N, N, T>& matrix)
    {
        for (std::size_t i = 0; i < N; ++i)
            matrix[i, i] = T{1};
    }(result);

    return result;
}

template<std::size_t N, typename T, std::size_t K>
inline void gauss(
    SmallMat<N, N, T> matrix,
    SmallMat<N, K, T>& result) noexcept
{
    using std::abs;

    for (std::size_t col = 0; col < N; ++col)
    {
        std::size_t pivot = col;

        for (std::size_t row = col + 1; row < N; ++row)
        {
            if (abs(matrix[row, col]) >
                abs(matrix[pivot, col]))
                pivot = row;
        }

        if (pivot != col)
        {
            for (std::size_t j = 0; j < N; ++j)
            {
                T temp = matrix[col, j];
                matrix[col, j] = matrix[pivot, j];
                matrix[pivot, j] = temp;
            }

            for (std::size_t j = 0; j < K; ++j)
            {
                T temp = result[col, j];
                result[col, j] = result[pivot, j];
                result[pivot, j] = temp;
            }
        }

        T divisor = matrix[col, col];

        for (std::size_t j = col; j < N; ++j)
            matrix[col, j] /= divisor;

        for (std::size_t j = 0; j < K; ++j)
            result[col, j] /= divisor;

        for (std::size_t row = 0; row < N; ++row)
        {
            if (row == col)
                continue;

            T factor = matrix[row, col];

            for (std::size_t j = col; j < N; ++j)
                matrix[row, j] -= factor * matrix[col, j];

            for (std::size_t j = 0; j < K; ++j)
                result[row, j] -= factor * result[col, j];
        }
    }
}

template<std::size_t N, typename T>
SmallMat<N, N, T> invert(
    SmallMat<N, N, T> const& matrix) noexcept
{
    auto result = make_identity<SmallMat<N, N, T>>();
    gauss(matrix, result);
    return result;
}

template<>
SmallMat<4, 4, float> invert(
    SmallMat<4, 4, float> const&) noexcept;

#endif