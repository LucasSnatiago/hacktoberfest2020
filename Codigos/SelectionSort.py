def SelectionSort(lista):
    
    for i in range(len(lista)-1):
        menor = lista[i]
        posJ = i

        for j in range(i+1, len(lista)):

            if menor > lista[j]:
                menor = lista[j]
                posJ = j

        lista[i], lista[posJ] = lista[posJ], lista[i]
        
    return lista