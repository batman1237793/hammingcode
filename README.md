# hammingcode
Программа реализует обработку информационного сообщения с помощью кода Хэмминга. Кодирование и декодирование сообщения происходит с использованием битов четности.
Функция calculateParity() вычисляет четность для указанных индексов битов в сообщении.
Функция encode() кодирует информационное сообщение, добавляя биты четности для обнаружения и исправления ошибок.
Функция decode() декодирует полученное закодированное сообщение, проверяет наличие ошибок с помощью синдрома и исправляет одну ошибку, если таковая обнаружена.
В функции main() пользователю предлагается выбрать действие: вывод исходного сообщения, кодирование сообщения, добавление ошибки в закодированное сообщение или декодирование сообщения. Исходное сообщение генерируется случайным образом, а добавление ошибки в закодированное сообщение также случайно изменяет один из битов.
Программа работает в бесконечном цикле до тех пор, пока пользователь не выберет выход из программы (ввод "0").
Таким образом, программа обеспечивает кодирование и декодирование информационного сообщения с возможностью обнаружения и исправления одиночных ошибок.
