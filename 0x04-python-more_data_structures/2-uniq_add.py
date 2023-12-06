def uniq_add(my_list=[]):
    unique_set = set()
    for num in my_list:
        if isinstance(num, int):
            unique_set.add(num)
    result = sum(unique_set)
    return result
