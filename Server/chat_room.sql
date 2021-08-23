BEGIN 

CREATE DATABASE IF NOT EXISTS `my_chat_room` DEFAULT CHARACTER SET utf8 DEFAULT COLLATE utf8_chinese_ci;
USE `my_chat_room`;


CREATE TABLE IF NOT EXISTS `users` (
    `uid` int(11) PRIMARY KEY AUTO_INCREMENT,
    `name` varchar(10) UNIQUE NOT NULL COMMENT '用户名',
    `password` varchar(128) NOT NULL COMMENT '密码',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='用户信息表';


CREATE TABLE IF NOT EXISTS `groups` (
    `gid` int(11) PRIMARY KEY AUTO_INCREMENT,
    `name` varchar(10) UNIQUE NOT NULL COMMENT '群聊名称',
    `owner` int(11) NOT NULL COMMENT '群主',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间',
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群聊信息表';


CREATE TABLE IF NOT EXISTS `friends` (
    `id` int(11) PRIMARY KEY AUTO_INCREMENT,
    `uid` int(11) NOT NULL COMMENT '用户名',
    `fuid` int(11) NOT NULL COMMENT '好友名',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间',
    UNIQUE KEY `friends_uid_fuid` (`uid`,`fuid`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='好友信息表';


CREATE TABLE IF NOT EXISTS `group_members` (
    `id` int(11) PRIMARY KEY AUTO_INCREMENT,
    `gid` int(11) NOT NULL COMMENT '群ID',
    `uid` int(11) NOT NULL COMMENT '群成员ID',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间',
    UNIQUE KEY `group_gid_uid` (`gid`， `uid`)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群成员信息表';


CREATE TABLE IF NOT EXISTS `group_messages` (
    `id` int(11) PRIMARY KEY AUTO_INCREMENT,
    `gid` int(11) NOT NULL COMMENT '群ID',
    `from_id` INT(11) NOT NULL COMMENT '发消息成员ID',
    `to_id` INT(11) NOT NULL COMMENT '发消息成员ID',
    `content` varchar(100) NOT NULL COMMENT '消息内容',
    `is_push` int(1) NOT NULL COMMENT '是否推送',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='群消息表';



CREATE TABLE IF NOT EXISTS `private_messages` (
    `id` int(11) PRIMARY KEY AUTO_INCREMENT,
    `from_id` int(11) NOT NULL COMMENT '发送者',
    `to_id` int(11) NOT NULL COMMENT '接收者',
    `content` varchar(100) NOT NULL COMMENT '消息内容',
    `is_push` int(1) NOT NULL COMMENT '是否推送',
    `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `updated_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更改时间'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='好友消息表';


COMMIT