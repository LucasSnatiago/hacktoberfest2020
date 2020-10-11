def insertion_sort(lista):
    fim = len(lista)
    for i in range(1, fim):
        for k in range(i):
            if lista[i] < lista[k]:
                x = lista[i]
                del lista[i]
                lista.insert(k, x)
    return lista