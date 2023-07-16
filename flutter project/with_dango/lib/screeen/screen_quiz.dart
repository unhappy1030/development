import 'package:flutter/material.dart';
import 'package:flutter_swiper_null_safety/flutter_swiper_null_safety.dart';
import 'package:with_dango/model/model_quiz.dart';

class QuizScreen extends StatefulWidget {
  final List<Quiz> quizs;
  QuizScreen({Key? key, required this.quizs}) : super(key: key);

  @override
  State<QuizScreen> createState() => _QuizScreenState();
}

class _QuizScreenState extends State<QuizScreen> {
  List<int> answers = [-1, -1, -1];
  List<bool> _anwerStates = [false, false, false, false];
  int _currentIndex = 0;
  @override
  Widget build(BuildContext context) {
    Size screensize = MediaQuery.of(context).size;
    double width = screensize.width;
    double height = screensize.height;
    return SafeArea(
        child: Scaffold(
      backgroundColor: Colors.deepPurple,
      body: Center(
          child: Container(
        decoration: BoxDecoration(
          borderRadius: BorderRadius.circular(20),
          border: Border.all(color: Colors.deepPurple),
        ),
        width: width * 0.85,
        height: height * 0.5,
        child: Swiper(
          physics: NeverScrollableScrollPhysics(),
          loop: false,
          itemCount: widget.quizs.length,
          itemBuilder: (BuildContext context, int index) {
            return _buildQuizCard(widget.quizs[index], width, height);
          },
        ),
      )),
    ));
  }

  Widget _buildQuizCard(Quiz quiz, double width, double height) {
    return Container(
      decoration: BoxDecoration(
        borderRadius: BorderRadius.circular(20),
        border: Border.all(color: Colors.deepPurple),
      ),
      child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[
            Container(
              padding: EdgeInsets.fromLTRB(0, width * 0.024, 0, width * 0.024),
              child: Text(
                'Q' + (_currentIndex + 1).toString() + '.',
                style: TextStyle(
                  fontSize: width * 0.06,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),
          ]),
    );
  }
}
