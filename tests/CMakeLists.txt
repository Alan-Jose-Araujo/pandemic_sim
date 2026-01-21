# 1. Incluir o módulo auxiliar do Catch2 para descoberta automática de testes
include(Catch)

# 2. Criar o executável para os testes unitários
# Podes adicionar mais ficheiros aqui conforme criares novos testes na pasta unit/
add_executable(unit_tests 
    unit/test_random_number_generator.cpp
    # unit/outro_teste.cpp
)

# 3. Ligar as dependências
# - simulator_lib: fornece o teu código e o caminho para os headers (include/)
# - Catch2::Catch2WithMain: fornece a biblioteca Catch2 e gera o main() automaticamente
target_link_libraries(unit_tests 
    PRIVATE 
        simulator_lib 
        Catch2::Catch2WithMain
)

# 4. Fazer com que o CMake "descubra" cada TEST_CASE individualmente
# Isto permite que vejas o progresso de cada teste ao usar o comando 'ctest'
catch_discover_tests(unit_tests)

# 5. Opcional: Criar um executável separado para testes de funcionalidade
# Se desejar manter testes de integração separados dos unitários
# add_executable(functional_tests 
#     functional/test_simulation_flow.cpp
# )

# target_link_libraries(functional_tests 
#     PRIVATE 
#         simulator_lib 
#         Catch2::Catch2WithMain
# )

# catch_discover_tests(functional_tests)