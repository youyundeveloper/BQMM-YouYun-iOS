//
//  YYBaseTableViewController.h
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import "YYBaseViewController.h"

@interface YYBaseTableViewController : YYBaseViewController<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, weak, readonly) UITableView * tableView;

@property (nonatomic, strong) NSMutableArray *dataSource;

@end
