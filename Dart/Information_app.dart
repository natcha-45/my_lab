// Copyright (c) 2019, the Dart project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme:
            ColorScheme.fromSeed(seedColor: Colors.lightGreen.shade300),
        useMaterial3: true,
      ),
      home: const MyHomePage(title: 'ข้อ 2'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  final String title;

  const MyHomePage({
    super.key,
    required this.title,
  }) : super();

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final centimeterController = TextEditingController();
  double inchvalue1 = 0;
  String inchvalue = '';

  void calculate() {
    inchvalue1 = ( double.parse(centimeterController.text) * 0.3937 );
    setState(() {
      inchvalue = inchvalue1.toStringAsFixed(4);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text(widget.title),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Container(
              width: 300,
              height: 300,
              decoration: BoxDecoration(
                color: Colors.lightGreen.shade100,
                borderRadius: BorderRadius.circular(15),
              ),
              child: Column(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                children: [
                  Container(
                    width: 200,
                    child: Column(
                        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                        children: [
                          TextField(
                              controller: centimeterController,
                              keyboardType: TextInputType.number,
                              decoration: InputDecoration(
                                suffixText: 'cm',
                                labelText: 'Enter Centimeter',
                                labelStyle: TextStyle(
                                    fontSize: 12,
                                    color: Colors.black,
                                    fontWeight: FontWeight.bold),
                                focusedBorder: OutlineInputBorder(
                                  borderRadius: BorderRadius.circular(15),
                                ),
                                fillColor: Colors.white,
                              ))
                        ]),
                  ),
                  Icon(
                    Icons.arrow_downward_sharp,
                    color: Colors.black,
                    size: 20,
                  ),
                  Container(
                    width: 200,
                    height: 55,
                    decoration: BoxDecoration(
                      //color: Colors.green,
                      borderRadius: BorderRadius.circular(15),
                      border: Border.all(
                        color: Colors.black,
                        width: 1,
                      ),
                    ),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Text('$inchvalue  inch',
                            style: TextStyle(
                              fontSize: 12,
                              color: Colors.black,
                              fontWeight: FontWeight.bold,
                            )),
                      ],
                    ),
                  ),
                  ElevatedButton(
                      style: ElevatedButton.styleFrom(
                          backgroundColor: Colors.green.shade200),
                      child: Text('แปลง',
                          style: TextStyle(
                              fontSize: 12,
                              color: Colors.black,
                              fontWeight: FontWeight.bold)),
                      onPressed: () {
                        calculate();
                        showDialog(
                          context: context,
                          builder: (BuildContext context) {
                            return AlertDialog(
                              title: Text('แปลง เซนติเมตร เป็น นิ้ว เสร็จสิ้น', style: TextStyle( fontSize: 12, color: Colors.black, fontWeight: FontWeight.bold ), ),
                              actions: <Widget>[
                                TextButton(
                                  onPressed: () {
                                    Navigator.pop(context, 'Cancel');
                                  },
                                  child: const Text('Cancel', style: TextStyle( fontSize: 12, fontWeight: FontWeight.bold ), ),
                                ),
                                TextButton(
                                  onPressed: () {
                                    Navigator.pop(context, 'OK', );
                                  },
                                  child: Text('OK', style: TextStyle( fontSize: 12, fontWeight: FontWeight.bold ), ),
                                ),
                              ],
                            );
                          },
                        );
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
