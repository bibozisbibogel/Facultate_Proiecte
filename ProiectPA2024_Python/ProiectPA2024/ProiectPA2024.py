# Proiect realizat de Stoian Cristian Georgian, Facultatea de Automatica, Calculatoare si Electronica, CR 1.2B
# Implementarea in Python (explicatiile le voi pune in prezentare)
import random
import string
def MinOfTwo(a, b): # Puteam sa folosesc direct min (functia din Python), dar vom mentine functia din programul C
    return min(a, b)
def NrMinimOperatii(regula, fragment_cod):
    n = len(regula)
    m = len(fragment_cod)
    dp = [[0] * (m + 1) for _ in range(n + 1)]

    for i in range(n + 1):
        dp[i][0] = i
    for j in range(m + 1):
        dp[0][j] = j

    for i in range(n):
        for j in range(m):
            if regula[i] == fragment_cod[j]:
                dp[i + 1][j + 1] = dp[i][j]
            else:
                insert_cost = dp[i + 1][j] + 1
                delete_cost = dp[i][j + 1] + 1
                replace_cost = dp[i][j] + 1
                if regula[i-1]==fragment_cod[j] and regula[i]==fragment_cod[j-1]:
                    swap_cost=dp[i-1][j-1]+1
                    replace_cost=MinOfTwo(replace_cost,swap_cost)
                dp[i + 1][j + 1] = MinOfTwo(MinOfTwo(insert_cost, delete_cost), replace_cost)

    return dp[n][m]

def random_string(length):
    charset = string.ascii_letters + string.digits + ",.-#'?!(){}`><-+@$%^&*~/:;\\"
    return ''.join(random.choice(charset) for _ in range(length))

def similar_string_generator(source):
    length = len(source)
    similar_string = list(source)

    num_errors = random.randint(1, length)
    for _ in range(num_errors):
        error_type = random.randint(0, 2)
        pos = random.randint(0, length - 1)

        if error_type == 0 and pos < length - 1:
            similar_string[pos], similar_string[pos + 1] = similar_string[pos + 1], similar_string[pos]
        elif error_type == 1 and length > 1:
            del similar_string[pos]
            length -= 1
        elif error_type == 2:
            similar_string[pos] = random.choice(string.ascii_lowercase)

    return ''.join(similar_string)

def main():
    chosen_method = int(input("Choose the method (1: manual input, 2: random input, 3: random similar input): "))
    if chosen_method == 1:
        regula = input("Enter the rule: ")
        fragment_cod = input("Enter the code fragment: ")
        nr = NrMinimOperatii(regula, fragment_cod)
        print(f"The minimum number of operations to transform the fragment to the rule is {nr}")
    elif chosen_method == 2:
        rule_length = int(input("Enter the length of the rule: "))
        regula_sirului = random_string(rule_length)
        fragment_length = int(input("Enter the length of the code fragment: "))
        fragment_incercat_cod = random_string(fragment_length)
        print(f"Random rule: {regula_sirului}")
        print(f"Random code fragment: {fragment_incercat_cod}")
        number_of_operations = NrMinimOperatii(regula_sirului, fragment_incercat_cod)
        print(f"The minimum number of operations to transform the fragment to the rule is {number_of_operations}")
    elif chosen_method == 3:
        lungime_sir_regula = int(input("Enter the length of the rule: "))
        sir_regula = random_string(lungime_sir_regula)
        print(f"Random rule: {sir_regula}")
        fragment_cod_similar = similar_string_generator(sir_regula)
        print(f"Random similar code fragment: {fragment_cod_similar}")
        nr_operations = NrMinimOperatii(sir_regula, fragment_cod_similar)
        print(f"The minimum number of operations to transform the fragment to the rule is {nr_operations}")
    else:
        print("Invalid method chosen.")

if __name__ == "__main__":
    main()
