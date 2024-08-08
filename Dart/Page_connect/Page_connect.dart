// Copyright 2019 the Dart project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file.

import 'package:flutter/material.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({Key? key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Page1'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  final String title;

  const MyHomePage({
    Key? key,
    required this.title,
  }) : super(key: key);

  @override
  State<MyHomePage> createState() => Page1State();
}

class Page1State extends State<MyHomePage> {
  String folder = 'assets/images/';
  String path = '';
  List<Map<String, dynamic>> people = [
    {"firstName": "James", "lastName": "Smith", "gender": "male", "age": 35},
    {"firstName": "Dave", "lastName": "Johnson", "gender": "male", "age": 28},
    {"firstName": "William", "lastName": "Brown", "gender": "male", "age": 12},
    {"firstName": "Olivia", "lastName": "Davis", "gender": "female", "age": 29},
    {"firstName": "Liam", "lastName": "Jones", "gender": "male", "age": 8},
    {"firstName": "Sophia", "lastName": "Wilson", "gender": "male", "age": 24},
    {"firstName": "Ethan", "lastName": "Taylor", "gender": "male", "age": 55},
    {"firstName": "Ava", "lastName": "Miller", "gender": "female", "age": 31},
  ];
  List<bool> like = [
    false,
    false,
    false,
    false,
    false,
    false,
    false,
    false,
  ];

  String setpath(int index) {
    index += 1;
    path = folder + '$index' + '.jpg';
    return (path);
  }

  String nametitle(int index) {
    if (people[index]["age"] >= 15 && people[index]["gender"] == 'male') {
      return ('Mister');
    } else if (people[index]["age"] < 15 && people[index]["gender"] == 'male') {
      return ('Master');
    } else {
      return ('Miss');
    }
  }

  Color colorlike(int index) {
    if (!like[index]) {
      return (const Color.fromARGB(255, 255, 255, 255));
    } else {
      return (Color.fromARGB(255, 255, 0, 0));
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: GridView.builder(
        scrollDirection: Axis.vertical,
        padding: EdgeInsets.all(20),
        itemCount: people.length,
        gridDelegate: SliverGridDelegateWithMaxCrossAxisExtent(
          maxCrossAxisExtent: 300,
          crossAxisSpacing: 20,
          mainAxisSpacing: 20,
        ),
        itemBuilder: (context, index) {
          return GridTile(
            child: Image.network(setpath(index), fit: BoxFit.cover),
            footer: GridTileBar(
              leading: Icon(
                Icons.favorite,
                color: colorlike(index),
              ),
              backgroundColor: Colors.black38,
              title: Text(
                '${nametitle(index)} ${people[index]["firstName"]} ${people[index]["lastName"]}',
              ),
              subtitle: Text('Age : ${people[index]["age"]}, '),
              trailing: ElevatedButton(
                child: Row(
                  children: [
                    Text('Next'),
                    Icon(Icons.arrow_forward_outlined),
                  ],
                ),
                onPressed: () async {
                  bool updatedLike = await Navigator.push(
                    context,
                    MaterialPageRoute(
                      builder: (context) => Page2(
                        person: people[index],
                        position: index + 1,
                        like: like[index],
                      ),
                    ),
                  );
                  if (updatedLike != null) {
                    setState(() {
                      like[index] = updatedLike;
                    });
                  }
                },
              ),
            ),
          );
        },
      ),
    );
  }
}

class Page2 extends StatefulWidget {
  final String folder = 'assets/images/';
  late String path;
  late bool like;
  final Map<String, dynamic> person;
  final int position;

  Page2({required this.person, required this.position, required this.like});

  @override
  _Page2State createState() => _Page2State();
}

class _Page2State extends State<Page2> {
  @override
  void initState() {
    super.initState();
    widget.path = '${widget.folder}${widget.position}.jpg';
  }

  String nametitle() {
    if (widget.person["age"] >= 15 && widget.person["gender"] == 'male') {
      return 'Mister';
    } else if (widget.person["age"] < 15 && widget.person["gender"] == 'male') {
      return 'Master';
    } else {
      return 'Miss';
    }
  }

  Color colorlike() {
    if (!widget.like) {
      return const Color.fromARGB(255, 255, 255, 255);
    } else {
      return Color.fromARGB(255, 255, 0, 0);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Page2'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            Container(
              height: 500,
              width: 500,
              child: Column(
                children: [
                  Image.network(widget.path, fit: BoxFit.cover),
                ],
              ),
            ),
            Container(
              child: Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Container(
                    child: ElevatedButton(
                      child: Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Icon(Icons.favorite, color: colorlike()),
                        ],
                      ),
                      onPressed: () {
                        setState(() {
                          widget.like = !widget.like;
                        });
                      },
                    ),
                  ),
                  Text(
                    ' ${nametitle()} ${widget.person["firstName"]} ${widget.person["lastName"]} Age : ${widget.person["age"]}',
                  ),
                ],
              ),
            ),
            Container(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  ElevatedButton(
                    child: Text('Back to Home Page'),
                    onPressed: () {
                      Navigator.pop(context, widget.like);
                    },
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}
