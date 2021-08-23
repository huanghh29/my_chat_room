BEGIN 

CREATE DATABASE IF NOT EXISTS `my_chat_room` DEFAULT CHARACTER SET utf8 DEFAULT COLLATE utf8_chinese_ci;
USE `my_chat_room`;

CREATE TABLE IF NOT EXISTS `users` (
    `uid` unsigned INT PRIMARY KEY AUTO_INCREMENT,
    `name` varchar(10) UNIQUE NOT NULL COMMENT '用户名',
    `password` varchar(128) NOT NULL COMMENT '密码',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户信息表';

CREATE TABLE IF NOT EXISTS `groups` (
    `gid` int unsigned PRIMARY KEY AUTO_INCREMENT,
    `name` varchar(10) UNIQUE NOT NULL COMMENT '群聊名称',
    `owner` varchar(10) NOT NULL COMMENT '群主',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群聊信息表';

CREATE TABLE IF NOT EXISTS `friends` (
    `id` int unsigned PRIMARY KEY AUTO_INCREMENT,
    `name` varchar(10) NOT NULL COMMENT '用户名',
    `fname` varchar(10) NOT NULL COMMENT '好友名',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间',
    UNIQUE name_fname (`name`,`fname`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='好友信息表';


CREATE TABLE IF NOT EXISTS `group_members` (
    `id` int unsigned PRIMARY KEY AUTO_INCREMENT,
    `group_name` varchar(10) NOT NULL COMMENT '群聊名称',
    `member_name` varchar(10) NOT NULL COMMENT '群成员名称',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间',
    UNIQUE group_member (`group_name`， `member_name`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群成员信息表';

CREATE TABLE IF NOT EXISTS `group_messages` (
    `id` int unsigned PRIMARY KEY AUTO_INCREMENT,
    `group_name` varchar(10) NOT NULL COMMENT '群聊名称',
    `send_name` varchar(10) NOT NULL COMMENT '发消息成员',
    `recv_name` varchar(10) NOT NULL COMMENT '接收成员',
    `message` varchar(100) NOT NULL COMMENT '消息内容',
    `is_push` varchar(100) NOT NULL COMMENT '是否推送',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群消息表';

CREATE TABLE IF NOT EXISTS `private_messages` (
    `id` int unsigned PRIMARY KEY AUTO_INCREMENT,
    `from_name` varchar(10) NOT NULL COMMENT '发送者',
    `to_name` varchar(10) NOT NULL COMMENT '接收者',
    `message` varchar(100) NOT NULL COMMENT '消息内容',
    `is_push` varchar(100) NOT NULL COMMENT '是否推送',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='好友消息表';

COMMIT