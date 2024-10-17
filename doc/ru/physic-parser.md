# Парсер физических выражений

Данный парсер, через физические формулы выражает необходимые переменные для решения определеннных задач.

### [Оглавление](index.md)



``` c++
void PhysicalCalculateForm::Calclulate()
{
  std::vector<double> value;
  std::vector<double> result;
  // Получаем массив данных
  QJsonArray jsonArray = GetJsonObject(":/source.json")["arrayData"].toArray();
  if(indexChoose <= jsonArray.count())
  {
      // Берем обьект по индексу
      QJsonObject object = jsonArray[indexChoose].toObject();
      // Берем массив значений переменных
      QJsonArray mathValueSymbolFormul = object["mathValueSymbolFormul"].toArray();
      // Берем массив формул
      QJsonArray formulExpression = object["formulExpression"].toArray();
      // Берем массив символов формул
      QJsonArray symbolFormul = object["symbolFormul"].toArray();

      for (int i = 0; i < ui->EditGroup->children().count() - 1; i++)
      {
          // Проверяем, если переменная равна нулю, то записываем значение из строки, иначе берем переменную из файла
          if(mathValueSymbolFormul[i].toDouble() == 0)
          {
            if(ui->EditGroup->children()[i+1]->metaObject()->className() == QString("QLineEdit")){
                QLineEdit *lineEdit = qobject_cast<QLineEdit*>(ui->EditGroup->children()[i+1]);
                Q_ASSERT(lineEdit != nullptr );
                value.push_back(lineEdit->text().toDouble());
            }
          }
          else
          {
              value.push_back(mathValueSymbolFormul[i].toDouble());
          }
      }
      if(formulExpression.count() == symbolFormul.count())
      {
          for (int i = 0; i < formulExpression.count(); i++)
          {
                 QString expression = formulExpression[i].toString();
                 for (int j = 0; j < value.size(); j++)
                 {
                     if(symbolFormul[j].toString().isEmpty())
                       continue;
                     else
                       expression.replace(symbolFormul[j].toString(), QString::number(value[j]));
                 }
                 try {
                    result.push_back(InterpreteExperssion(expression.toStdWString()));
                 } catch (...) { }
          }
      }
      else
      {
          throw std::logic_error("Количество переменных не равно количесту значений переменных. Исправьте JSON файл");
      }
  }
    else
    {
      throw std::logic_error("Индекс формулы больше, чем иммееться формул");
    }
  CheckLineEditIsEmpty(result);
}
```

Теперь давайте по этапно разберемся что тут происходит.
## Этап 1
Изначально у нас создается два динамических массива. Один с значением переменных, другой для расчета каждой переменной в физической формуле. Они играют здесь ключевую роль. В них бы будем класть данные из полей, в которые вводит данные пользователь. Также из JSON файла, мы извлекаем формулы и переменнны для расчетов.
## Этап 2
Далее, у нас идет проверка, если текущий индекс формулы, которую выбрал пользователь, меньше или равно количеству возможных формул, то тогда выполняется код. А иначе бы выводим ошибку о том, что не можем найти обходимую формулу.
## Этап 3
Далее из массива данныз с JSON, мы дастаем необходимый нам обьект по индексу, заданному пользователем. Из обьекта, мы дастаем переменную (типо F - сила), начальное значение переменной, а также саму формулу, по которой будет происходить расчет.
## Этап 4
Сначало нам нужно извлечь данные из полей ввода. Далее, мы проверяем, если начальная переменная равна 0, то мы записываем значение из поля ввода, а иначе из данных в JSON файле. 
## Этап 5
Если количество переменных, и формулы, выведенные не сходяться, то мы выводим ошибку для исправления этого недоразумения. Далее мы пробегаемся через цикл по каждой формуле и проводим замену буквенных переменных на числовые значения. После чего, данное выражение мы отправляем математическому парсеру.
## Результат
После всего этого, математический парсер просчитывает полносью все выражения. После чего, массив данных с готовыми результатами отправляется пользователю на экран.