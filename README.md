<div dir="rtl" lang="he">

# טבלה ארגונית עם איטרטורים

במרבית הארגונים הגדולים ניתן לשרטט תרשים ברור המתאר את ההיררכיה הארגונית. תרשים זה נקרא טבלה ארגונית, ניתן לקרוא עליו [כאן](https://en.wikipedia.org/wiki/Organizational_chart)

במטלה זו נממש מחלקה המייצגת מבנה ארגוני היררכי ואיטרטורים שיכולים לעבור על המבנה הארגוני באחת מהאופים הבאים:

1. שיטת level-order - באופן איטרציה זה נתחיל מראש הארגון (לדוגמה מנכ"ל, רמטכ"ל, מפכ"ל) ונרד באופן "רוחבי" דרך הדרגים השונים עד לאובייקט הזוטר ביותר בארגון.  
דוגמה לאיטרציה על ארגון פרטי באופן זה:  
מנכ"ל יודפס ראשון, לאחריו כל הסמנכ"לים, אחריהם מנהלים בכירים, אחריהם מנהלים זוטרים וכו'.

2. שיטת reverse-level-order - בדיוק ההפך משיטת level-order. נעבור על כל הדרג הזוטר ביותר בארגון ונעלה באופן "רוחבי" דרך סולם הדרגות עד שנגיע לראש הארגון.

3. מעבר לעומק - שיטה זו מזכירה את שיטת המעבר preorder על עץ בינארי, רק שהפעם העץ שלנו לא בינארי. 



שם המחלקה: `OrgChart`.
השיטות הדרושות (ראו בקובץ [Demo.cpp](https://github.com/cpp-exercises-5782/orgchart-a/blob/main/Demo.cpp) לפרטים):

* `add_root` - מקבלת קלט אחד ושמה אותו בשורש של העץ. אם כבר יש משהו בשורש, הוא מוחלף.
* `add_sub` מקבלת שני קלטים. אדם (או מחלקה) שכבר קיימים במבנה הארגוני ואדם נוסף (או מחלקה נוספת) אשר מדווחים לאדם הראשון ונמצאים מתחתיו בהיררכיה הארגונית.
* `begin_level_order()`, `end_level_order()` - מחזירות איטרטורים לצורך מעבר בסדר level order (אב - בן - בן - נכד).
* `begin_reverse_order()`, `end_reverse_order()` - מחזירות איטרטורים לצורך מעבר בסדר reverse level order (נכד - נכד - בן - בן - אב).
* `begin_preorder()`, `end_preorder()` - מחזירות איטרטורים לצורך מעבר בסדר preorder (אב - בן - נכד - בן - נכד)

* אופרטור פלט - מדפיס את העץ בפורמט הגיוני כלשהו לבחירתכם.


תוספות לחלק ב:
* **יעילות**: האיטרטור צריך להיות יעיל ככל האפשר מבחינת זיכרון. בפרט, אין לשמור את כל תוכן העץ בגוף האיטרטור. נסו למצוא פתרון יעיל יותר.
* כתבו בנאי מעתיק ואופרטור השמה המבצעים **העתקה עמוקה**, כמו שלמדנו בשיעור 5.

* הפקודות `make test1`, `make test2`, `make test3`, `make tidy`, `make valgrind` צריכות לעבוד ללא שגיאות.
* כתבו תוכנית ראשית יצירתית לצורך הדגמה


אין לשנות את הקבצים הנתונים, אלא רק להוסיף קבצים חדשים.

יש לפתור את המטלה באופן עצמאי.

* מותר להתייעץ עם סטודנטים אחרים או לחפש מידע באינטרנט;
אסור להעתיק קטעי-קוד שלמים מסטודנטים אחרים או מהאינטרנט.
* יש לדווח על כל עזרה שקיבלתם, מסטודנטים אחרים או מהאינטרנט, בהתאם ל[תקנון היושר של המחלקה](https://www.ariel.ac.il/wp/cs/wp-content/uploads/sites/88/2020/08/Guidelines-for-Academic-Integrity.pdf).

</div>