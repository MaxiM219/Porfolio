
valores = ["0","1","2","3","3","4","5","6","7","8","9","A","B","C","D","E","F","a","b","c","d","e","f"]

cambio = "GOON"

ayuda = "help"
ayuda1 = "HELP"

defecto = True

def imprimir_ayuda():
    print("Programa creado por Max1323")
    print("Para el uso de este programa es necesario saber de punteros.")
    print("El programa necesita que insertes 4 digito que son los últimos 4 digitos en hexadecimales del comienzo del texto.\n")
    print("Por ejemplo: La palabra: 'Elfir' (magia) está ubicado en 00020C76.")
    print("Utiliza solo los últimos 4 digitos: 0C76.")
    print("Escribelos así: 760C. Escribirlos así te devolverá su puntero '668C' y luego buscarlo con el editor hexadecimal.")
    print("También puedes invertir el orden, escribiendo 'GOON'. Con esto no tendrás que dar vuelta los digitos. Ejemplo: '0C76' resultado '668C'.\n")
    print("Este programa solo fue hecho para el juego de SD Gundam Story Knight Gundam Legend.")

def main():
    print("Para cambiar el orden de escritura escribe\n'GOON'\nIngrese 'help' o 'HELP' para obtener más información.")
    while True:
        valor = pedir(True)
        resultado = sumar(valor)
        nuevo_valor = pedir(False)
        if nuevo_valor != "":
            resultado2 = sumar(nuevo_valor)
            imprimir(resultado, resultado2)
        else:
            imprimir(resultado, "")

def pedir(primera_vuelta):
    if(primera_vuelta):
        print("-------------------------")
    valor = input("Ingrese valor hex: ")
    largo = len(valor)
    if primera_vuelta == False and largo == 0:
        return valor
    if largo != 4:
        print("Vuelve a ingresar. Solo 4 caracteres.")
        return pedir(True)
    
    if(valor == cambio):
        global defecto
        if(defecto == True):
            print("cambiado")
            defecto = False
        elif(defecto == False):
            print("Por defecto")
            defecto = True

    if(valor == ayuda or valor == ayuda1):
        imprimir_ayuda()
    
    for c in valor:
        if c not in valores:
            print("Vuelve a ingresar")
            return pedir(True)
    
    if(defecto == False):
        valor = valor[-2:] + valor[:2]
    return valor.upper()

def sumar(valor):
    esto = valor[:2]
    if 0x00 <= int(esto, 16) <= 0x0F:
            ultimo = int(valor[-2:],16)
            ultimo -= int("01", 16)
            valor = valor[:2] + hex(ultimo)[-2:]
    resultado = hex(int(valor, 16) + int("f000", 16))
    ultimos_digitos = int(resultado[-2:], 16)
    correccion = int("40", 16)
    menos_cuarenta = int("80", 16)

    if  int("40", 16) <= ultimos_digitos < int("80", 16):
        ultimos_digitos = ultimos_digitos + correccion
    elif int("00", 16) <= ultimos_digitos <= int("3F", 16):
        ultimos_digitos += menos_cuarenta
    elif ultimos_digitos > int("BF", 16):
        ultimos_digitos = ultimos_digitos - correccion

    resultado = resultado[:-2] + hex(ultimos_digitos)[-2:]
    res = resultado[2:].upper()
    if(len(res) >= 5):
        res = res[1:]
        return res
    return res

def imprimir(resultado, resultado2):
    print(resultado, " -> ", resultado2)

main()