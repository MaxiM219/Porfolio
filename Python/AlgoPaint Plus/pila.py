class Pila:
    def __init__(self):
        self.items = []
    
    def apilar(self, x):
        self.items.append(x)

    def ver_tope(self):
        return self.items[-1]


    def desapilar(self):
        return self.items.pop()

    def esta_vacia(self):
        return len(self.items) == 0