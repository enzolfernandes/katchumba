# Katchumba — minhas contribuições ao seguidor de linha da TERA

Reúno neste fork os estudos e códigos do robô seguidor de linha da [equipe TERA](https://github.com/roboticatera/Katchumba). O histórico é coletivo; minha contribuição identificada está nos ajustes do sketch `KagueGPT2.0`.

## Minha contribuição

No [commit b871be2, de 19/07/2023](https://github.com/enzolfernandes/katchumba/commit/b871be246d5069632f625aaf8558d443a9214025), alterei constantes e tipos, removi declarações duplicadas e reorganizei a leitura dos sensores em [KagueGPT/KagueGPT2.0.ino](KagueGPT/KagueGPT2.0.ino). Esse registro documenta mudanças de implementação; não mede desempenho do robô.

## Navegação

| Pasta | Conteúdo |
| --- | --- |
| [KagueGPT](KagueGPT) | Duas versões de sketch de seguimento de linha |
| [SegueLinha](SegueLinha), [SeguidorArduino](SeguidorArduino), [codigoKague](codigoKague) | Outras implementações e estudos de controle |
| [TesteSensorQTR8RC](TesteSensorQTR8RC) | Leitura e calibração de sensores QTR |
| [TesteSensorMotor](TesteSensorMotor), [TesteSensoresEsp](TesteSensoresEsp) | Estudos de integração de sensores e motores |
| [sensores](sensores), [testeinfra](testeinfra), [TesteSemeel](TesteSemeel) | Experimentos auxiliares |

Há variantes para Arduino e ESP32. A placa, a pinagem, os limiares e a forma de PWM precisam ser conferidos no sketch escolhido; as pastas não formam uma única aplicação.

## Preparar um sketch

```shell
git clone https://github.com/enzolfernandes/katchumba.git
cd katchumba
```

Escolha apenas uma variante. Na Arduino IDE, crie uma pasta de sketch com o mesmo nome do `.ino` escolhido e copie somente seus arquivos necessários. Isso evita compilar juntas as duas versões em `KagueGPT/`. Instale o suporte à placa e as bibliotecas importadas por essa variante, como `QTRSensors` no exemplo QTR. Revise pinagem e versões das APIs antes de compilar.

## Estado da documentação

Esta revisão inspecionou o código e o histórico, sem compilar ou acionar hardware. Há sketches exploratórios: o exemplo QTR referencia `motor1a` e `motor1b` sem declaração nesse arquivo; `SegueLinha.ino` contém comparações encadeadas que precisam de revisão em C++. Esses pontos foram identificados e o firmware foi preservado. Não há um ambiente único com versões fixadas ou relatório consolidado de testes no repositório.

## Origem

Fork de [roboticatera/Katchumba](https://github.com/roboticatera/Katchumba), preservando os demais autores e dependências. Não há licença geral declarada na raiz inspecionada.

*README acrescentado em 17/10/2026; a contribuição histórica acima é de 2023.*
