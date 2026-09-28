def shape(func):
    def decor(*args, **kwargs):
        result = func(*args, **kwargs)
        print(f'Table with shape {len(result)}x{len(result[0].keys())}')
        return result
    return decor

@shape
def read_csv(file_name, dtype=None):
    result = []
    with open(file_name, 'r') as file:
        cols = file.readline().replace('\n', '').split(',')
        rows = map(lambda row: row.replace('\n', '').split(','), file.readlines())

        if not (dtype is None):
            for typed_col in dtype.keys():
                if typed_col not in cols: raise ValueError("Unknown column in dtype")

        for row in rows:
            if len(row) != len(cols): raise ValueError('Incorrect values count')
            row_data = {}
            for col_i in range(len(cols)):
                value = row[col_i]
                col = cols[col_i]

                if not (dtype is None) and col in dtype:
                    try:
                        value = dtype[col](value)
                    except:
                        raise ValueError(f"Cannot convert value '{value}' in column '{col}' to {dtype[col].__name__}")

                row_data[col] = value

            result.append(row_data)

    return result

def head(data, n=5):
    if n < 0:
        raise ValueError('n must be non-negative')
    return data[:n]

@shape
def filter_rows(data, condition):
    return [v for v in data if condition(v)]

def select_columns(data, columns):
    if len(data) == 0: return []

    exists_cols = data[0].keys()
    for select_col in columns:
        if select_col not in exists_cols: raise ValueError('Unknown column')

    return [{row_data[0]:row_data[1] for row_data in row.items() if row_data[0] in columns} for row in data]

def add_column(data, name, func):
    exists_cols = data[0].keys()
    if name in exists_cols: raise ValueError("Column already exists")

    result = []
    for row in data:
        row_data = row.copy()
        row_data[name] = func(row)
        result.append(row_data)

    return result

def aggregate(data, column, func):
    exists_cols = data[0].keys()
    if column not in exists_cols: raise ValueError("Unknown column")
    return func([row[column] for row in data])

def column_sum(data, column):
    return aggregate(data, column, sum)

def column_min(data, column):
    return aggregate(data, column, min)

def column_max(data, column):
    return aggregate(data, column, max)

def column_mean(data, column):
    return aggregate(data, column, lambda values: sum(values) / len(values))

def unique(data, column):
    return aggregate(data, column, lambda values: list(set(values)))

def value_counts(data, column):
    return aggregate(data, column, lambda values: {value: values.count(value) for value in set(values)})

def iter_csv(file_name, dtype=None):
    result = []
    with open(file_name, 'r') as file:
        cols = file.readline().replace('\n', '').split(',')

        if not (dtype is None):
            for typed_col in dtype.keys():
                if typed_col not in cols: raise ValueError("Unknown column in dtype")

        while True:
            raw_row = file.readline()
            if not raw_row: break
            row = raw_row.replace('\n', '').split(',')
            if len(row) != len(cols): raise ValueError('Incorrect values count')
            row_data = {}
            for col_i in range(len(cols)):
                value = row[col_i]
                col = cols[col_i]

                if not (dtype is None) and col in dtype:
                    try:
                        value = dtype[col](value)
                    except:
                        raise ValueError(f"Cannot convert value '{value}' in column '{col}' to {dtype[col].__name__}")

                row_data[col] = value

            yield row_data

# data = head(read_csv('test.txt', dtype={'age': int}), 5)
# adults = filter_rows(data, lambda row: int(row['age']) >= 18)
# result = select_columns(data, ["name", "city"])
# result = add_column(
#     data,
#     "adult",
#     lambda row: row["age"] >= 18
# )
# result = aggregate(data, "age", max)
# result = column_mean(data, "age")
# result = unique(data, "city")
# result = value_counts(data, "city")
# print(result)
#
# for row in iter_csv('test.txt', dtype={'age': int}):
#     print(row)